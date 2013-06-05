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

#define MS 1000		//!< Multiply by this define to obtain miliseconds from microseconds.

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
 */
static en_game_return_code gBrain_scenery_load_elem(st_scen_elem *elem);

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
	st_scen_elem *ss_elem = NULL;

	ll_elem = mixed_llist_get_elem(Scenery.elem_list, 2);
	if (ll_elem == NULL) {
		error("Failed to recover the elemnt.");
		return GAME_RET_ERROR;
	}
	ss_elem = (st_scen_elem *)ll_elem->data;
	debug("Element recovered! Key: %d", ss_elem->v_elem.key);


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


static en_game_return_code gBrain_scenery_load_elem(st_scen_elem *elem)
{
	CHECK_INITIALIZED(Scenery.initialized);

	unsigned int elem_key = -1;
	st_list_item *list_item = NULL;
	st_scen_elem *scen_elem = NULL;
	en_mixed_return_code mret;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	/* Insert element into the scenery elements list. */
	if (Scenery.elem_list->item_counter == 0) {
		list_item = mixed_llist_add_elem(Scenery.elem_list, elem, sizeof(st_scen_elem), true);
	}
	else {
		list_item = mixed_llist_add_elem(Scenery.elem_list, elem, sizeof(st_scen_elem), false);
	}
	/* Valided mixedAPI answer. */
	if (list_item == NULL) {
		debug("Failed to add scenery element into the list");
		return GAME_RET_ERROR;
	}

	/* Fill the message. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;

	/* Copy element data into message. */
	BRAIN_FILL_V_ELEM(msg.v_elem, elem->v_elem);

	/* Requests to the game video module to update the visual list. */
	mret = mixed_mqueue_send(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Receive and validate the answer. */
	CHECK_EXCEPT(gBrain_scenery_load_elem_ack(&elem_key), GAME_RET_HALT);

	/* Acknowledge was successful. Update the element into the list. */
	scen_elem = (st_scen_elem *)list_item->data;
	scen_elem->v_elem.key = elem_key;

	debug("Element visual key: %d", scen_elem->v_elem.key);

	return GAME_RET_SUCCESS;
}

static en_game_return_code gBrain_scenery_load_elem_ack(unsigned int *key)
{
	const unsigned char retry_max = 5;
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
		mret = mixed_mqueue_recv(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, 0, 10*MS);
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
		if (game_msg->type == GAME_ACTION_RET_SCREEN_ELEM) {

			debug("Received screen return msg. Operation %s.",
				(game_msg->v_elem.key != GVIDEO_INVALID_KEY)? "success":"error");

			/* Close mqueue. */
			mixed_mqueue_close_sender(&gbrain_mqueue, GBRAIN_MQUEUE_NAME);

			/* Validate acknowledge. */
			if (game_msg->v_elem.key != GVIDEO_INVALID_KEY) {
				*key = game_msg->v_elem.key;
				return GAME_RET_SUCCESS;
			}
			else {
				return GAME_RET_ERROR;
			}
		}
		else if (game_msg->type == GAME_ACTION_HALT_MODULE) {
			debug("Received a halt solicitation while loading a scenery. Quitting...");
			return GAME_RET_HALT;
		}
		else {
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
	}

	return GAME_RET_ERROR;
}

