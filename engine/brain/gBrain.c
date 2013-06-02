#include <mqueue.h>
#include <pthread.h>

#include "gBrain.h"
#include "gBrain_defines.h"
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

	/* Setup mqueue. */
	debug("Setup mqueue for receiving requests.");
	mret = mixed_mqueue_create(&gbrain_mqueue,
							GBRAIN_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_RECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		debug("Failed to setup mqueue.");
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
        bytes_read = mq_receive(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			debug("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gBrain_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	mixed_mqueue_close(&gbrain_mqueue, GVIDEO_MQUEUE_NAME);
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

