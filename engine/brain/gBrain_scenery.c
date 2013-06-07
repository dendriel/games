#include "gBrain_scenery.h"
#include "gBrain_defines.h"
#include "gBrain_structs.h"

#include "game_defines.h"
#include "game_structs.h"

#include "llist.h"
#include "llist_defines.h"
#include "llist_structs.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"
#include "macros.h"

#define MSEC (float) 0.001
#define USEC (float) 0.000001

/**************************************************************************************************/
/**
 *	\b Scenery elements list.
 */
static struct {
	bool initialized;		//!< Tells that the gameVideo_screen is initialized.
	st_list *elem_list;		//!< Used to hold all the scenery elements.
} Scenery = {false, NULL};

/**************************************************************************************************/
/**
 *	\b Add the given element to the scenery elements list and request to the game video module to 
 *	add a visual element in the visual list (that will be put in the screen).
 *	\p elem The element data to be added into the list.
 *	\r GAME_RET_SUCCESS if could add the element both Scenery and Visual list; 
 *	GAME_RET_ERROR if something went wrong and the element was not added.
 */
static en_game_return_code gBrain_scenery_load_elem(st_scen_elem *elem);

/**************************************************************************************************/
/**
 *	\b Remove the given element from both Scenery and Visual list.
 *	\p index The element index into the Scenery elements list.
  *	\r GAME_RET_SUCCESS if could remove the element from the lists.
 */
static en_game_return_code gBrain_scenery_rem_elem(const unsigned int index);

/**************************************************************************************************/
/**
 *	\b Try to receive a message from the game video module to acknowledge the insert of the element 
 *	into the visual list.
 *	\r GAME_RET_SUCCESS if the element was successully added to the visual list and the visual list 
 *	key for the element was filled (v_elem.key); GAME_RET_HALT if received a halt solicitation 
 *	while receiving messages; GAME_RET_ERROR for any operation error.
 */
static en_game_return_code gBrain_scenery_load_elem_ack(unsigned int *key);

/**************************************************************************************************/

en_game_return_code gBrain_scenery_init(void)
{
	if (!Scenery.initialized) {
		int ret;

		/* Initialize a linked list to hold the visual objects. */
		ret = llist_init(&Scenery.elem_list);
		if (ret != 0) {
			critical("Failed to initialize scenery linked list.");
			return GAME_RET_ERROR;
		}
		Scenery.initialized = true;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

void gBrain_scenery_finish(void)
{
	if (Scenery.initialized) {
		/* Free the linked list allocated memory. */
		debug("Free scenery elements list...");
		llist_destroy(&Scenery.elem_list);

		/* Reset the structure (also, the initialized flag is set to false). */
		memset(&Scenery, 0, sizeof(Scenery));
	}
	debug("Game brain scenery sub-module has finished successfully.");
}

/**************************************************************************************************/

en_game_return_code gBrain_scenery_load(void)
{
	st_scen_elem sc_elem;
int i;
for (i = 0; i < 2; i++) {
	memset(&sc_elem, 0, sizeof(sc_elem));
	/* Fill visual elements. */
	BRAIN_FILLNLOAD_V_ELEM(sc_elem.v_elem,
						GVIDEO_VTYPE_SCEN_STATIC,
						0, 0,
						"./media/img/800x600.bmp");

	debug("Load scenary element.");
	CHECK_ERROR_EXCEPT(gBrain_scenery_load_elem(&sc_elem),
						GAME_RET_HALT,
						"Failed to load an element.");

	memset(&sc_elem, 0, sizeof(sc_elem));
	/* Fill visual elements. */
	BRAIN_FILLNLOAD_V_ELEM(sc_elem.v_elem,
						GVIDEO_VTYPE_ELEM_STATIC,
						90, 90,
						"./media/img/espada.bmp");

	debug("Load sword element.");
	CHECK_ERROR_EXCEPT(gBrain_scenery_load_elem(&sc_elem),
						GAME_RET_HALT,
						"Failed to load an element.");

	memset(&sc_elem, 0, sizeof(sc_elem));
	/* Fill visual elements. */
	BRAIN_FILLNLOAD_V_ELEM(sc_elem.v_elem,
						GVIDEO_VTYPE_ELEM_STATIC,
						200, 200,
						"./media/img/house.bmp");

	debug("Load house element.");
	CHECK_ERROR_EXCEPT(gBrain_scenery_load_elem(&sc_elem),
						GAME_RET_HALT,
						"Failed to load an element.");

	/* verify the elem. */
	st_list_item *ll_elem = NULL;

	ll_elem = mixed_llist_get_elem(Scenery.elem_list, 2);
	if (ll_elem == NULL) {
		error("Failed to recover the element. Not found!");
	}

	debug("Will remove an element!");
	if (gBrain_scenery_rem_elem(2) != GAME_RET_SUCCESS) {
		error("Element could not be removed!");
	}
}

//
//	ret = mixed_mqueue_send_msg(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
//	if (ret != GAME_RET_SUCCESS) {
//		debug("Failed to add espada!!!");
//	}
//
//	/* Update image. */
//	memset(&msg, 0, sizeof(st_game_msg));
//	/* Fill the message. */
//	msg.id = GBRAIN_MOD_ID;
//	msg.type = GAME_ACTION_UPD_SCREEN_ELEM_POS;
//	/* Fill visual elements. */
//	msg.v_elem.key = 1; // we should have received this reference from game video module after add an element.
//	msg.v_elem.h = 95;
//	msg.v_elem.v = 95;
//
//	while (msg.v_elem.h != 120) {
//		ret = mixed_mqueue_send_msg(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
//		if (ret != GAME_RET_SUCCESS) {
//			debug("Failed to add espada!!!");
//		}
//		msg.v_elem.h++;
//		msg.v_elem.v++;
//		usleep(100000);
//	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_scenery_load_elem(st_scen_elem *elem)
{
	CHECK_INITIALIZED(Scenery.initialized);

	unsigned int elem_key = -1;
	st_list_item *list_item = NULL;
	en_mixed_return_code mret;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	/* Fill the message. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;
	/* Copy element data into message. */
	BRAIN_FILL_V_ELEM(msg.v_elem, elem->v_elem);

	/* Send the request. */
	mret = mixed_mqueue_send(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Receive and validate the answer. */
	CHECK_EXCEPT(gBrain_scenery_load_elem_ack(&elem_key), GAME_RET_HALT);

	/* Acknowledge was successful. Add the element to the list. */
	elem->v_elem.key = elem_key;
	list_item = mixed_llist_add_elem(Scenery.elem_list, elem, sizeof(st_scen_elem));
	if (list_item == NULL) {
		debug("Failed to add scenery element into the list");
		// ask visual module to remove the item.
		return GAME_RET_ERROR;
	}

	debug("Element added. Visual key: %d", ((st_scen_elem *)list_item->data)->v_elem.key);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_scenery_rem_elem(const unsigned int index)
{
	CHECK_INITIALIZED(Scenery.initialized);

	unsigned int elem_key = -1;
	en_mixed_return_code mret;
	st_game_msg msg;
	st_list_item *list_item= NULL;

	list_item = mixed_llist_get_elem(Scenery.elem_list, index);
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
	CHECK_EXCEPT(gBrain_scenery_load_elem_ack(&elem_key), GAME_RET_HALT);

	/* Acknowledge was successful. Remove the element to the Scenery list. */
	mixed_llist_rem_elem(Scenery.elem_list, index);

	debug("Element removed. Index was: %d", index); 

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_scenery_load_elem_ack(unsigned int *key)
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
			debug("Received a halt solicitation while loading a scenery. Quitting...");
			return GAME_RET_HALT;
		}

		if (game_msg->type != GAME_ACTION_RET_SCREEN_ELEM) {
			debug("Received a message that cannot process. Message type: %d", game_msg->type);
			/* As received an invalid message, is fair to retry. */
			if (retries < retry_max) {
				debug("Will retry to receive the game video module answer.");
				retries++;
				continue;
			}
			else {
				debug("Failed to receive the game video module answer. Stop reading...");
				return GAME_RET_ERROR;
			}
		}

		debug("Received screen return msg. Operation %s.",
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

