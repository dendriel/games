#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "gSystem_loop.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gSystem_defines.h"
#include "mixedAPI.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\b Extern from game System main module.
 */
extern char Gsystem_label[GAME_MOD_LABEL_SIZE];

/**************************************************************************************************/
/**
 *	\b Process requests and answers (from own requests).
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT_PROCESS if received a
 *	halting solicitation message.
 */
static en_game_return_code gSystem_process_message(st_game_msg *game_msg);

/**************************************************************************************************/

static en_game_return_code gSystem_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GSYSTEM_MOD_ID:
				debug(Gsystem_label, "Unknown message received from System module. Type: %d.", type);
		break;

		case GCONTROLLER_MOD_ID:
			if (type == GAME_ACTION_HALT_MODULE) {
				return GAME_RET_HALT;
			}
			else {
				debug(Gsystem_label, "Unknown message received from Controller module. Type: %d.", type);
			}

		case GVIDEO_MOD_ID:
		case GBRAIN_MOD_ID:
			debug(Gsystem_label, "Received a message from an unauthorized module. Module ID: %d; Message type: %d", id, type);
		break;

		default:
			debug(Gsystem_label, "Received message from invalid module. id: %d", id);
		break;
	}


	return GAME_RET_SUCCESS;
}


/*************************************************************************************************/

void gSystem_loop(void)
{
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gsystem_mqueue;

	/* Setup mqueue. */
	debug(Gsystem_label, "Setup mqueue for receiving requests.");
	mret = mixed_mqueue_create(&gsystem_mqueue,
							GSYSTEM_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_CRRECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		critical("Failed to setup mqueue.");
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
		bytes_read = mq_receive(gsystem_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			error("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gSystem_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			debug(Gsystem_label, "Received halt solicitation. Will exit...");
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	mixed_mqueue_close(&gsystem_mqueue, GSYSTEM_MQUEUE_NAME);
	debug(Gsystem_label, "System module exited the loop.");
}

