#include "gBrain_scenery.h"
#include "gBrain_defines.h"
#include "gBrain_structs.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gBrain_gvideo_intf.h"

#include "llist.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Extern from gVideo main module.
 */
extern char Gbrain_label[GAME_MOD_LABEL_SIZE];

/**************************************************************************************************/
/**
 *	\b Scenery elements list.
 */
static struct {
	bool initialized;		//!< Tells that the gameVideo_screen is initialized.
	st_list *elem_list;		//!< Used to hold all the scenery elements.
} Scenery = {false, NULL};


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
		debug(Gbrain_label, "Free scenery elements list...");
		llist_destroy(&Scenery.elem_list);

		/* Reset the structure (also, the initialized flag is set to false). */
		memset(&Scenery, 0, sizeof(Scenery));
	}
	debug(Gbrain_label, "Game brain scenery sub-module has finished successfully.");
}

/**************************************************************************************************/

// TESTING PURPOSE ONYL!!
en_game_return_code gBrain_scenery_load(void)
{
	st_scen_elem sc_elem;

	memset(&sc_elem, 0, sizeof(sc_elem));
	/* Fill visual elements. */
	BRAIN_FILLNLOAD_V_ELEM(sc_elem.v_elem,
						GVIDEO_VTYPE_SCEN_STATIC,
						0, 0,
						"./media/img/zelda_map.bmp",
						GVIDEO_INVALID_KEY);

	debug(Gbrain_label, "Load scenary element.");
	CHECK_ERROR_EXCEPT(gBrain_gvideo_intf_add_elem(&sc_elem, Scenery.elem_list),
						GAME_RET_HALT,
						"Failed to load an element.");


#if 0
	/* verify the elem. */
	st_list_item *ll_elem = NULL;

	ll_elem = mixed_llist_get_elem(Scenery.elem_list, 1);
	if (ll_elem == NULL) {
		error("Failed to recover the element. Not found!");
	}
	debug(Gbrain_label, "Element loaded %d", ((st_scen_elem *)ll_elem->data)->v_elem.key);

	debug(Gbrain_label, "Will remove an element!");
	if (gBrain_gvideo_intf_rem_elem(2, Scenery.elem_list) != GAME_RET_SUCCESS) {
		error("Element could not be removed!");
	}

	/* Fill visual elements. */
	unsigned int h = 95;
	unsigned int v = 95;

	while (h != 130) {
		CHECK_ERROR_EXCEPT(gBrain_gvideo_intf_upd_elem_pos(1, h, v, Scenery.elem_list),
							GAME_RET_HALT,
							"Failed to update the element.");
		h++;
		v++;
		usleep(100000);
	}
#endif

	return GAME_RET_SUCCESS;
}

