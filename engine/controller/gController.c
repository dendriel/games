#include <mqueue.h>
#include <pthread.h>

#include "gController.h"
#include "gController_defines.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gController_keyboard.h"

#include "mixedAPI.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\b Game controller module name. Used to debug.
 */
char Gcontroller_label[GAME_MOD_LABEL_SIZE] = "";

/**************************************************************************************************/
/**
 *	\d Processing thread. Receive and process message commands.
 *	\p data Unused.
 */
static void gController_thread(void *data);

/**************************************************************************************************/
/**
 *	\b Process only system requests.
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT_PROCESS if received a
 *	halting solicitation message.
 */
static en_game_return_code gController_process_message(st_game_msg *game_msg);

/**************************************************************************************************/

static en_game_return_code gController_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GSYSTEM_MOD_ID:
			if (type == GAME_ACTION_HALT_MODULE) {
				return GAME_RET_HALT;
			}
			else {
				debug(Gcontroller_label, "Unknown message received from gameSystem module. Type: %d.", type);
			}
		break;

		case GVIDEO_MOD_ID:
		case GCONTROLLER_MOD_ID:
		case GBRAIN_MOD_ID:
			debug(Gcontroller_label, "Received a message from an unauthorized module. Module ID: %d; Message type: %d", id, type);
		break;

		default:
			debug(Gcontroller_label, "Received message from invalid module. id: %d", id);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gController_thread(void *data)
{
	pthread_t gcontroller_keyboard_tid;
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gcontroller_mqueue;

	debug(Gcontroller_label, "Initialize game controller keyboard sub-module.");
	ret = pthread_create(&gcontroller_keyboard_tid, NULL, (void *)gController_keyboard_thread, NULL);
	if (ret != 0) {
		critical("Failed to create game controller keyboard sub-module thread.");
		exit(-1);
	}

	/* Setup mqueue. */
	debug(Gcontroller_label, "Setup mqueue for receiving requests.");
	mret = mixed_mqueue_create(&gcontroller_mqueue,
							GCONTROLLER_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_CRRECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		critical("Failed to setup mqueue.");
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
		bytes_read = mq_receive(gcontroller_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			error("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gController_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			debug(Gcontroller_label, "Received halt solicitation. Will exit...");
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	mixed_mqueue_close(&gcontroller_mqueue, GVIDEO_MQUEUE_NAME);
	debug(Gcontroller_label, "Finished successfully.");
	pthread_exit(0);
}

/*************************************************************************************************/

en_game_return_code gController_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE])
{
	int ret;

	if (strlen(mod_name)) {
		strncpy(Gcontroller_label, mod_name, sizeof(Gcontroller_label));
	}

	ret = pthread_create(thread_id, NULL, (void *)gController_thread, NULL);
	if (ret != 0) {
		debug(Gcontroller_label, "Failed to create %s module thread.", Gcontroller_label);
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}
