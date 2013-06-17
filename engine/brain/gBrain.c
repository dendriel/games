#include <mqueue.h>
#include <pthread.h>

#include "gBrain.h"
#include "gBrain_defines.h"
#include "gBrain_scenery.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gBrain_process.h"

#include "mixedAPI.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Game brain module name. Used to debug.
 */
char Gbrain_label[GAME_MOD_LABEL_SIZE] = "";

/**************************************************************************************************/
/**
 *	\d Processing thread. Receive and process message commands.
 *	\p data Unused.
 */
static void gBrain_thread(void *data);

/**************************************************************************************************/
/**
 *	\b Process game play (initialization, actions, etc) requests.
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT_PROCESS if received a
 *	halting solicitation message.
 */
static en_game_return_code gBrain_process_message(st_game_msg *game_msg);

/**************************************************************************************************/
/**
 *	\b Process Controller requests.
 *	\p game_msg Data from the request.
 */
static void gBrain_process_controller_message(st_game_msg *game_msg);

/**************************************************************************************************/
/**
 *	\b Process System requests.
 *	\p game_msg Data from the request.
 */
static en_game_return_code gBrain_process_system_message(st_game_msg *game_msg);

/**************************************************************************************************/

static void gBrain_process_controller_message(st_game_msg *game_msg)
{
	en_game_msg_type type;

	type = game_msg->type;
	switch (type) {

		case GAME_ACTION_MOVE_UP:
		case GAME_ACTION_MOVE_RIGHT:
		case GAME_ACTION_MOVE_DOWN:
		case GAME_ACTION_MOVE_LEFT:
		{
			debug(Gbrain_label, "Received a request to move an element. Direction: %d", game_msg->type);
			gBrain_process_element_movement(&game_msg->type);
		}
		break;

		default:
			debug(Gbrain_label, "Invalid message type received from game Controller module. type: %d", type);
		break;
	}
}

/**************************************************************************************************/

static en_game_return_code gBrain_process_system_message(st_game_msg *game_msg)
{
	en_game_msg_type type;

	type = game_msg->type;
	switch (type) {

		case GAME_ACTION_HALT_MODULE:
			return GAME_RET_HALT;
		break;

		case GAME_ACTION_LOAD_SCENERY:
		{
			debug(Gbrain_label, "Received a request to load a scenery.");
			CHECK_ERROR_EXCEPT(gBrain_scenery_load(),
								GAME_RET_HALT,
								"Failed to process te load scenery request.");
		}
		break;

		default:
			debug(Gbrain_label, "Invalid message type received from System module. type: %d", type);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GVIDEO_MOD_ID:
			debug(Gbrain_label, "Unknown message received from game video module. Type: %d.\n", type);
		break;

		case GSYSTEM_MOD_ID:
			CHECK_EXCEPT(gBrain_process_system_message(game_msg), GAME_RET_HALT);
		break;

		case GCONTROLLER_MOD_ID:
			gBrain_process_controller_message(game_msg);
		break;

		case GBRAIN_MOD_ID:
			debug(Gbrain_label, "Unknown message received from game brain module. Type: %d.", type);
		break;

		default:
			debug(Gbrain_label, "Received message from invalid module. id: %d", id);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gBrain_thread(void *data)
{
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gbrain_mqueue;

	debug(Gbrain_label, "Initialize game brain sub-module scenery.");
	ret = gBrain_scenery_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialized game brain sub-module scenery.");
		exit(-1);
	}

	/* Setup mqueue. */
	debug(Gbrain_label, "Setup mqueue for receiving requests.");
	mret = mixed_mqueue_create(&gbrain_mqueue,
							GBRAIN_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_CRRECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		critical("Failed to setup mqueue.");
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
		bytes_read = mq_receive(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			error("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gBrain_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			debug(Gbrain_label, "Received halt solicitation. Will exit...");
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	gBrain_scenery_finish();
	mixed_mqueue_close(&gbrain_mqueue, GVIDEO_MQUEUE_NAME);
	debug(Gbrain_label, "Finished successfully.");
	pthread_exit(0);
}

/*************************************************************************************************/

en_game_return_code gBrain_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE])
{
	int ret;

	if (strlen(mod_name)) {
		strncpy(Gbrain_label, mod_name, sizeof(Gbrain_label));
	}

	ret = pthread_create(thread_id, NULL, (void *)gBrain_thread, NULL);
	if (ret != 0) {
		debug(Gbrain_label, "Failed to create module thread.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

