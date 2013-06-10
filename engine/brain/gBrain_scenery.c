#include "gBrain_scenery.h"
#include "gBrain_defines.h"
#include "gBrain_structs.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gBrain_gvideo_intf.h"
#include "gVideo_defines.h"

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
/**
 *	\b Create and add element to scenery list.
 *	\p type Element type.
 *	\p h Initial horizontal position of the element.
 *	\p h Initial vertical position of the element.
 *	\p img_path The image source that will be splitted to make the element views.
 *	\p h_size Horizontal size of the element views.
 *	\p v_size Vertical size of the element views.
 *	\p direction Initial looking direction of the element.
 *	\r GAME_RET_SUCCESS for operation success; GAME_RET_HALT if received halt solicitation while 
 *	processing; GAME_RET_ERROR if something went wrong.
 */
static en_game_return_code gBrain_scenery_add_elem(
	const en_visual_type type,
	const unsigned int h,
	const unsigned int v,
	const char *img_path,
	const unsigned int h_size,
	const unsigned int v_size,
	en_visual_image_pos direction);

/**************************************************************************************************/
/**
 *	\b Create and add map to scenery list.
 *	\p type Element type.
 *	\p h Initial horizontal position of the element.
 *	\p h Initial vertical position of the element.
 *	\p img_path The image source that will be splitted to make the element views.
 *	\r GAME_RET_SUCCESS for operation success; GAME_RET_HALT if received halt solicitation while 
 *	processing; GAME_RET_ERROR if something went wrong.
 */
static en_game_return_code gBrain_scenery_add_map(
	const en_visual_type type,
	const unsigned int h,
	const unsigned int v,
	const char *img_path);

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

static en_game_return_code gBrain_scenery_add_elem(
	const en_visual_type type,
	const unsigned int h,
	const unsigned int v,
	const char *img_path,
	const unsigned int h_size,
	const unsigned int v_size,
	en_visual_image_pos direction)
{
	unsigned int h_ind;
	unsigned int v_ind;
	unsigned int index = 1;
	st_scen_elem sc_elem;

	memset(&sc_elem, 0, sizeof(sc_elem));

	sc_elem.v_elem.image[GVIDEO_IMG_SRC] = load_bitmap(img_path, NULL);
	if (sc_elem.v_elem.image[GVIDEO_IMG_SRC] == NULL) {
		error("Failed to load source bitmap.");
		return GAME_RET_ERROR;
	}

	/* Split the image. */
	for(v_ind = 0; v_ind < 4; v_ind++) {
		for(h_ind = 0; h_ind < 4; h_ind++) {
			sc_elem.v_elem.image[index] = create_bitmap(h_size, v_size);
			blit(sc_elem.v_elem.image[GVIDEO_IMG_SRC], sc_elem.v_elem.image[index],
					h_size*h_ind, v_size*v_ind,
					0, 0,
					h_size, v_size);
			index++;
		}
	}

	sc_elem.v_elem.type = type;
	sc_elem.v_elem.h = h;
	sc_elem.v_elem.v = v;
	sc_elem.v_elem.img_index = direction;

	debug(Gbrain_label, "Load element.");
	CHECK_ERROR_EXCEPT(gBrain_gvideo_intf_add_elem(&sc_elem, Scenery.elem_list),
						GAME_RET_HALT,
						"Failed to load an element.");

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gBrain_scenery_add_map(
	const en_visual_type type,
	const unsigned int h,
	const unsigned int v,
	const char *img_path)
{
	st_scen_elem sc_elem;

	memset(&sc_elem, 0, sizeof(sc_elem));

	sc_elem.v_elem.image[GVIDEO_IMG_SRC] = load_bitmap(img_path, NULL);
	if (sc_elem.v_elem.image[GVIDEO_IMG_SRC] == NULL) {
		error("Failed to load source bitmap.");
		return GAME_RET_ERROR;
	}

	sc_elem.v_elem.type = type;
	sc_elem.v_elem.h = h;
	sc_elem.v_elem.v = v;
	sc_elem.v_elem.img_index = GVIDEO_IMG_SRC;

	debug(Gbrain_label, "Load element.");
	CHECK_ERROR_EXCEPT(gBrain_gvideo_intf_add_elem(&sc_elem, Scenery.elem_list),
						GAME_RET_HALT,
						"Failed to load an element.");

	return GAME_RET_SUCCESS;
}
/**************************************************************************************************/

// TESTING PURPOSE ONYL!!
en_game_return_code gBrain_scenery_load(void)
{
	/* Load scenery. */
	debug(Gbrain_label, "Load map element.");
	CHECK_ERROR_EXCEPT(gBrain_scenery_add_map(GVIDEO_VTYPE_SCEN_STATIC,
						0, 0,
						"./media/img/zelda_map.bmp"),
						GAME_RET_HALT,
						"Failed to load the map element.");

int i;
/*TODO: next move is create a update element image index into the video screen module, make
 * this loop use the function, then, make controller send requests to updated (only for testing).
 * The controller will just send the "move down" event and the brain will make it.
 */
for (i = 1; i < 17; i++) {
	/* Load hero. */
	debug(Gbrain_label, "Load hero element.");
	CHECK_ERROR_EXCEPT(gBrain_scenery_add_elem(GVIDEO_VTYPE_ELEM_STATIC,
						90+i*20, 90+i*20,
						"./media/img/warrior.bmp",
						GVIDEO_ELEM_SIZE_H, GVIDEO_ELEM_SIZE_V,
						i),
						GAME_RET_HALT,
						"Failed to load the warrior element.");
	usleep(500*1000);
}

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

