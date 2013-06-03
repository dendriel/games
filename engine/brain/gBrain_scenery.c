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
 *	\r GAME_RET_SUCCESS if the element was successully added to the visual list; 
 *	GAME_RET_ERROR otherwise.
 */
static en_game_return_code gBrain_scenery_load_elem_ack(void);

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
}

/**************************************************************************************************/

en_game_return_code gBrain_scenery_load(void)
{
	en_game_return_code ret;
	st_scen_elem sc_elem;

	memset(&sc_elem, 0, sizeof(sc_elem));

	/* Fill visual elements. */
	sc_elem.v_elem.type = GVIDEO_VTYPE_SCEN_STATIC;
	sc_elem.v_elem.h = 0;
	sc_elem.v_elem.v = 0;
	sc_elem.v_elem.image = load_bitmap("./media/img/800x600.bmp", NULL);

	if (!sc_elem.v_elem.image) {
		critical("Failed to load scenery bitmap.");
		return GAME_RET_ERROR;
	}

	debug("Load element for scenary.");
	ret = gBrain_scenery_load_elem(&sc_elem);
	if (ret == GAME_RET_HALT) {
		return GAME_RET_HALT;
	}
	else if (ret != GAME_RET_SUCCESS) {
		debug("Failed to load an element.");
		return GAME_RET_ERROR;
	}

//	memset(&msg, 0, sizeof(st_game_msg));
//
//	/* Fill the message. */
//	msg.id = GBRAIN_MOD_ID;
//	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;
//	/* Fill visual elements. */
//	msg.v_elem.type = GVIDEO_VTYPE_ELEM_STATIC;
//	msg.v_elem.h = 90;
//	msg.v_elem.v = 90;
//	msg.v_elem.image = load_bitmap("./media/img/espada.bmp", NULL);
//
//	if (!msg.v_elem.image) {
//		critical("Failed to load  espada bitmap.");
//		return GAME_RET_ERROR;
//	}
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

	en_game_return_code ret;
	st_list_item *list_item = NULL;
	en_mixed_return_code mret;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	/* Insert element into the scenery elements list. */
	if (Scenery.elem_list->item_counter == 0) {
		list_item = mixed_llist_add_elem(Scenery.elem_list, elem, sizeof(st_scen_elem), true);
	}
	else {
		list_item = mixed_llist_add_elem(Scenery.elem_list, elem, sizeof(st_scen_elem), true);
	}
	/* Valided mixedAPI answer. */
	if (list_item == NULL) {
		debug("Failed to add scenery element into the list");
		return GAME_RET_ERROR;
	}

	/* Fill the message. */
	msg.id = GBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;

	msg.v_elem.h = elem->v_elem.h;
	msg.v_elem.v = elem->v_elem.v;
	msg.v_elem.type = elem->v_elem.type;
	msg.v_elem.image = elem->v_elem.image;

	/* Requests to the game video module to update the visual list. */
	mret = mixed_mqueue_send_msg(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (mret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	ret = gBrain_scenery_load_elem_ack();
	if (ret == GAME_RET_HALT) {
		return GAME_RET_HALT;
	}
	else if (ret != GAME_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

static en_game_return_code gBrain_scenery_load_elem_ack(void)
{
	en_mixed_return_code mret;
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	mqd_t gbrain_mqueue;

	mret = mixed_mqueue_open(&gbrain_mqueue, GBRAIN_MQUEUE_NAME, GAME_MQUEUE_SIZE, GAME_MQUEUE_RECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		debug("Failed to open mqueue in read mode.");
		return GAME_RET_ERROR;
	}

	struct timespec tm;

	while(true) {
		clock_gettime(CLOCK_REALTIME, &tm);
		tm.tv_sec += 5;

		memset(&recvd_data, 0, sizeof(recvd_data));
		//bytes_read = mq_receive(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);
		bytes_read = mq_timedreceive(gbrain_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL, &tm);

		if (bytes_read == -1) {
			error("Failed to receive message. errno: %d; msg: %s.", errno, strerror(errno));
			if (errno == ETIMEDOUT) {
				break;
			}
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		if (game_msg->type == GAME_ACTION_RET_SCREEN_ELEM) {
			debug("Received an add screen elem return.");
			debug("h: %d; v: %d; key: %d", game_msg->v_elem.h, game_msg->v_elem.v, game_msg->v_elem.key);
		}
		else if (game_msg->type == GAME_ACTION_HALT_MODULE) {
			debug("Received a halt solicitation while loading a scenery. Quitting...");
			return GAME_RET_HALT;
		}
	}

	return GAME_RET_SUCCESS;
}



