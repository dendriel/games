#include <mqueue.h>
#include <pthread.h>

#include "gBrain.h"
#include "gBrain_defines.h"
#include "gBrain_scenery.h"
#include "game_defines.h"
#include "game_structs.h"

#include "mixedAPI.h"

#include "debug.h"


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

static en_game_return_code gBrain_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GVIDEO_MOD_ID:
			debug("Unknown message received from game video module. Type: %d.\n", type);
		break;

		case GSYSTEM_MOD_ID:
			if (type == GAME_ACTION_HALT_MODULE) {
				return GAME_RET_HALT;
			}
			else if (type == GAME_ACTION_LOAD_SCENERY) {
				debug("Received a request to load a scenery.");
				en_game_return_code ret;
				ret = gBrain_scenery_load();
				if (ret == GAME_RET_HALT) {
					return GAME_RET_HALT;
				}
				else if (ret != GAME_RET_SUCCESS){
					debug("Failed to process te load scenery request.");
				}
			}
			else {
				debug("Unknown message received from gameSystem module. Type: %d.", type);
			}
		break;

		case GCONTROL_MOD_ID:
			debug("Unknown message received from game control module. Type: %d.", type);
		break;

		case GBRAIN_MOD_ID:
			debug("Unknown message received from game brain module. Type: %d.", type);
		break;

		default:
			debug("Received message from invalid module. id: %d", id);
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

	debug("Initialize game brain scenery sub-module.");
	ret = gBrain_scenery_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialized game brain scenery sub-module.");
		exit(-1);
	}

	/* Setup mqueue. */
	debug("Setup mqueue for receiving requests.");
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
			debug("Received halt solicitation. Will exit...");
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	gBrain_scenery_finish();
	mixed_mqueue_close(&gbrain_mqueue, GVIDEO_MQUEUE_NAME);
	debug("Game brain module has finished successfully.");
	pthread_exit(0);
}

/*************************************************************************************************/

en_game_return_code gBrain_init(pthread_t *thread_id)
{
	int ret;

	ret = pthread_create(thread_id, NULL, (void *)gBrain_thread, NULL);
	if (ret != 0) {
		debug("Failed to create brain module thread.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

