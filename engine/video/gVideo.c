#include <fcntl.h>
#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>
#include <mqueue.h>
#include <errno.h>

#include "gVideo.h"
#include "gVideo_defines.h"
#include "gVideo_structs.h"
#include "gVideo_screen.h"
#include "game_structs.h"
#include "game_defines.h"
#include "gSystem_defines.h"
#include "gBrain_defines.h"

#include "mixedAPI.h"
#include "mixedAPI_defines.h"
#include "alarm.h"
#include "alarm_defines.h"
#include "alarm_structs.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\d Processing thread. Receive and process message commands.
 *	\p data Unused.
 */
static void gVideo_thread(void *data);

/**************************************************************************************************/
/**
 *	\b Create an periodical alarm to trigger the update of the screen.
 *	\p alarm_entry Filled with a reference to the created alarm.
 *	\r GAME_RET_SUCCESS if could create the alarm; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gVideo_set_screen_trigger(int *alarm_entry);

/**************************************************************************************************/
/**
 *	\b Remove the update screen alarm entry.
 *	\p Reference to the alarm (received at alarm creation).
 */
static void gVideo_remove_screen_trigger(int alarm_entry);

/**************************************************************************************************/
/**
 *	\b Process game video requests.
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT if received a
 *	halting solicitation message.
 */
static en_game_return_code gVideo_process_message(st_game_msg *game_msg);


/**************************************************************************************************/

static en_game_return_code gVideo_set_screen_trigger(int *alarm_entry)
{
	en_alarm_ret_code ret;
	st_alarm alarm;
	st_game_msg *gvideo_msg;

	memset(&alarm, 0, sizeof(alarm));
	memset(&gvideo_msg, 0, sizeof(st_game_msg));

	/* Fill up alarm message. */
	alarm.wait_time = GAMEVIDEO_SCREEN_UPDATE_US;
	alarm.repeat = true;
	alarm.priority = GAME_MQUEUE_PRIO_1;
	strncpy(alarm.dest_mqueue, GVIDEO_MQUEUE_NAME, sizeof(alarm.dest_mqueue));

	gvideo_msg = (st_game_msg *) malloc(sizeof(st_game_msg));
	if (!gvideo_msg) {
		debug("Failed to allocate memory for gvideo_msg.");
		return GAME_RET_ERROR;
	}

	memset(gvideo_msg, 0, sizeof(*gvideo_msg));
	gvideo_msg->type = GAME_ACTION_UPDATE_SCREEN;
	gvideo_msg->id = GVIDEO_MOD_ID;
	alarm.data = (void *)gvideo_msg;
	alarm.data_size = sizeof(st_game_msg);

	/* Set the trigger alarm for drawing the buffer into screen. */
	ret = alarm_set_trigger(&alarm, alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to setup update screen trigger. ret: %d", ret);
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gVideo_remove_screen_trigger(int alarm_entry)
{
	en_alarm_ret_code ret;

	ret = alarm_remove_trigger(alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to remove update screen alarm entry.");
	}
}

/**************************************************************************************************/

static void gVideo_processe_brain_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	bool re_send = false;

	type = game_msg->type;
	switch (type) {

		case GAME_ACTION_ADD_SCREEN_ELEM:
		{
			debug("Received solicitation to add an element to the visual list.");
			re_send = true;
			int index;
			index = gVideo_screen_add_elem(&game_msg->v_elem);
			if (index == GAME_RET_ERROR) {
				error("Failed to add element type %d into screen list.", game_msg->v_elem.type);
				game_msg->v_elem.key = GVIDEO_INVALID_KEY;
			}
			else {
				debug("Item type %d with index %d was added to visual list.", game_msg->v_elem.type, index);
				game_msg->v_elem.key = index;
			}
			game_msg->type = GAME_ACTION_RET_SCREEN_ELEM;
		}
		break;

		case GAME_ACTION_UPD_SCREEN_ELEM_POS:
		{
			re_send= true;
			int ret;
			ret = gVideo_screen_update_elem_pos(&game_msg->v_elem);
			if (ret != GAME_RET_SUCCESS) {
				error("Failed to update the element.");
				/* Fill the element key with invalid value to indicate the error. */
				game_msg->v_elem.key = GVIDEO_INVALID_KEY;
			}
			game_msg->type = GAME_ACTION_RET_SCREEN_ELEM;
		}
		break;

		default:
			debug("Invalid message type received from gameBrain module. type: %d", type);
		break;
	}

	/* Re-send the packet to the request with the same packet. */
	if (re_send == true) {
		debug("Re-send the message to game brain module. h: %d; v: %d; key: %d", 
			game_msg->v_elem.h, game_msg->v_elem.v, game_msg->v_elem.key);
		en_mixed_return_code mret;
		mret = mixed_mqueue_send_msg(GBRAIN_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, game_msg);
		if (mret != MIXED_RET_SUCCESS) {
			error("Failed to re-send the message to game brain module. Type was: %d.", type);
		}
	}

	return;
}

/**************************************************************************************************/

static en_game_return_code gVideo_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GVIDEO_MOD_ID:
			if (type == GAME_ACTION_UPDATE_SCREEN) {
				gVideo_screen_update();
			}
			else {
				debug("Unknown message received from game video module. Type: %d.\n", type);
			}
		break;

		case GSYSTEM_MOD_ID:
			if (type == GAME_ACTION_HALT_MODULE) {
				debug("Received halt solicitation. Will exit...");
				return GAME_RET_HALT;
			}
			else {
				debug("Unknown message received from gameSystem module. Type: %d.\n", type);
			}
		break;

		case GBRAIN_MOD_ID:
			gVideo_processe_brain_message(game_msg);
		break;

		default:
			debug("Received message from invalid module. id: %d", id);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gVideo_thread(void *data)
{
	int alarm_entry;
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gvideo_mqueue;

	/* Setup game video sub-module "screen". */
	debug("Initialize game video screen sub-module.");
	ret = gVideo_screen_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game video screen sub-module.");
		exit(-1);
	}

	/* Setup update screen trigger. */
	debug("Setup update screen alarm.");
	ret = gVideo_set_screen_trigger(&alarm_entry);
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to setup screen alarm.");
		gVideo_screen_finish();
		exit(-1);
	}

	/* Setup mqueue. */
	debug("Setup mqueue for receiving requests.");
	mret = mixed_mqueue_create(&gvideo_mqueue,
							GVIDEO_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_CRRECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		debug("Failed to setup mqueue.");
		gVideo_remove_screen_trigger(alarm_entry);
		gVideo_screen_finish();
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
        bytes_read = mq_receive(gvideo_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			debug("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gVideo_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			gVideo_remove_screen_trigger(alarm_entry);
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	mixed_mqueue_close(&gvideo_mqueue, GVIDEO_MQUEUE_NAME);
	gVideo_screen_finish();
	debug("Game video module has finished successfully.");
	pthread_exit(0);
}

/*************************************************************************************************/

en_game_return_code gVideo_init(pthread_t *thread_id)
{
	int ret;

	ret = pthread_create(thread_id, NULL, (void *)gVideo_thread, NULL);
	if (ret != 0) {
		debug("Failed to create video module thread.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

