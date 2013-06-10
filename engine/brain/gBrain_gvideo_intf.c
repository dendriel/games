#include "gBrain_gvideo_intf.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gBrain_defines.h"
#include "gBrain_structs.h"

#include "llist.h"
#include "llist_defines.h"
#include "llist_structs.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Extern from game Brain main module.
 */
extern char Gbrain_label[GAME_MOD_LABEL_SIZE];

/**************************************************************************************************/
/**
 *	\b Try to receive a message from the game video module to acknowledge the insert of the element 
 *	into the visual list.
 *	\p key Will hold the answer data if there is one.
 *	\r GAME_RET_SUCCESS if the element was successully added to the visual list and the visual list 
 *	key for the element was filled (v_elem.key); GAME_RET_HALT if received a halt solicitation 
 *	while receiving messages; GAME_RET_ERROR for any operation error.
 */
static en_game_return_code gBrain_gvideo_intf_elem_ack(unsigned int *key);


/**************************************************************************************************/

en_game_return_code gBrain_gvideo_intf_add_elem(st_scen_elem *elem, st_list *elem_list)
{
	unsigned int elem_key = -1;
	st_list_item *list_item = NULL;
	en_mixed_return_code mret;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	/* Fill the message. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;
	/* Copy element data into message. */
	memcpy(&msg.v_elem, &elem->v_elem, sizeof(msg.v_elem));

	/* Send the request. */
	mret = mixed_mqueue_send(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Receive and validate the answer. */
	CHECK_EXCEPT(gBrain_gvideo_intf_elem_ack(&elem_key), GAME_RET_HALT);

	/* Acknowledge was successful. Add the element to the list. */
	elem->v_elem.key = elem_key;
	list_item = mixed_llist_add_elem(elem_list, elem, sizeof(st_scen_elem));
	if (list_item == NULL) {
		error("Failed to add scenery element into the list");
		return GAME_RET_ERROR;
	}

	debug(Gbrain_label, "Element added. Visual key: %d", ((st_scen_elem *)list_item->data)->v_elem.key);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gBrain_gvideo_intf_rem_elem(const unsigned int index, st_list *elem_list)
{
	unsigned int elem_key = -1;
	en_mixed_return_code mret;
	st_game_msg msg;
	st_list_item *list_item= NULL;

	list_item = mixed_llist_get_elem(elem_list, index);
	if (list_item == NULL) {
		return GAME_RET_ERROR;
	}

	memset(&msg, 0, sizeof(msg));

	/* Fill the message. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_REM_SCREEN_ELEM;
	msg.v_elem.key = ((st_scen_elem *)list_item->data)->v_elem.key;

	/* Send the request. */
	mret = mixed_mqueue_send(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Receive and validate the answer. */
	CHECK_EXCEPT(gBrain_gvideo_intf_elem_ack(&elem_key), GAME_RET_HALT);

	/* Acknowledge was successful. Remove the element to the Scenery list. */
	mixed_llist_rem_elem(elem_list, index);

	debug(Gbrain_label, "Element removed. Index was: %d", index); 

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gBrain_gvideo_intf_upd_elem_pos(
	const unsigned int index,
	const unsigned int h,
	const unsigned int v,
	st_list *elem_list)
{
	unsigned int elem_key = -1;
	en_mixed_return_code mret;
	st_game_msg msg;
	st_list_item *list_item= NULL;
	st_scen_elem *elem = NULL;

	list_item = mixed_llist_get_elem(elem_list, index);
	if (list_item == NULL) {
		return GAME_RET_ERROR;
	}

	elem = (st_scen_elem *)list_item->data;

	memset(&msg, 0, sizeof(msg));

	/* Fill the message header. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_UPD_SCREEN_ELEM_POS;
	/* Fill the message data. */
	msg.v_elem.key = elem->v_elem.key;
	msg.v_elem.h = h;
	msg.v_elem.v = v;

	/* Send the request. */
	mret = mixed_mqueue_send(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Receive and validate the answer. */
	CHECK_EXCEPT(gBrain_gvideo_intf_elem_ack(&elem_key), GAME_RET_HALT);

	elem->v_elem.h = h;
	elem->v_elem.v = v;

	debug(Gbrain_label, "Element updated. Index: %d. New position h: %d, v: %d", index, elem->v_elem.h, elem->v_elem.v);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_gvideo_intf_elem_ack(unsigned int *key)
{
	const unsigned char retry_max = 5;
	const float timeout_sec = 1;
	unsigned char retries = 0;
	
	en_mixed_return_code mret;
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	st_game_msg *game_msg = NULL;
	mqd_t gbrain_mqueue;

	/* Open the mqueue to receive the game video module answer. */
	mret = mixed_mqueue_open(&gbrain_mqueue, GBRAIN_MQUEUE_NAME, GAME_MQUEUE_SIZE, GAME_MQUEUE_RECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		error("Failed to open mqueue in read mode.");
		return GAME_RET_ERROR;
	}

	while(true) {
		/* Try to receive the answer. */
		mret = mixed_mqueue_recv(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, timeout_sec, 0);
		if (mret == MIXED_RET_TIMEOUT) {
			error("Game video module is not responding.");
			mixed_mqueue_close_sender(&gbrain_mqueue, GBRAIN_MQUEUE_NAME);
			return GAME_RET_ERROR;
		}
		else if (mret != MIXED_RET_SUCCESS) {
			mixed_mqueue_close_sender(&gbrain_mqueue, GBRAIN_MQUEUE_NAME);
			return GAME_RET_ERROR;
		}

		/* Verify received data. */
		game_msg = (st_game_msg *)recvd_data;

		if (game_msg->type == GAME_ACTION_HALT_MODULE) {
			debug(Gbrain_label, "Received a halt solicitation while loading a scenery. Quitting...");
			return GAME_RET_HALT;
		}

		if (game_msg->type != GAME_ACTION_RET_SCREEN_ELEM) {
			debug(Gbrain_label, "Received a message that cannot process. Message type: %d", game_msg->type);
			/* As received an invalid message, is fair to retry. */
			if (retries < retry_max) {
				debug(Gbrain_label, "Will retry to receive the game video module answer.");
				retries++;
				continue;
			}
			else {
				debug(Gbrain_label, "Failed to receive the game video module answer. Stop reading...");
				return GAME_RET_ERROR;
			}
		}

		debug(Gbrain_label, "Received screen return msg. Operation %s.",
			(game_msg->reply != GAME_MSG_RET_OP_SUCCESS)? "error":"success");

		/* Close mqueue. */
		mixed_mqueue_close_sender(&gbrain_mqueue, GBRAIN_MQUEUE_NAME);

		/* Validate acknowledge. */
		if (game_msg->reply != GAME_MSG_RET_OP_SUCCESS) {
			return GAME_RET_ERROR;
		}

		*key = game_msg->v_elem.key;

		return GAME_RET_SUCCESS;
	}

	return GAME_RET_ERROR;
}

