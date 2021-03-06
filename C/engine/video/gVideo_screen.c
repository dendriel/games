#include <allegro.h>
#include <stdbool.h>

#include "gVideo_screen.h"
#include "gVideo_screen_defines.h"
#include "game_defines.h"
#include "game_structs.h"
#include "gSystem_defines.h"

#include "llist.h"
#include "llist_defines.h"
#include "llist_structs.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Extern from game video main module.
 */
extern char Gvideo_label[GAME_MOD_LABEL_SIZE];

/**************************************************************************************************/
/**
 *	\b Hold data used to process game screen issues.
 */
static struct {
	bool initialized;				//!< Tells that the gameVideo_screen is initialized.
	st_list *list;					//!< Visual List - Hold figures that will draw into the screen.
	BITMAP *screen_buffer;			//!< Used to draw the figure of the elements.
} Visual = {false, NULL, NULL};


/**************************************************************************************************/
/**
 *	\b Verify if the given visual element is valid.
 *	\p elem The element to be verified.
 *	\r GAME_RET_SUCCESS if the element is valid; GAME_RET_ERROR for invalid element.
 */
static en_game_return_code gVideo_screen_check_elem(st_visual *elem);


/**************************************************************************************************/

en_game_return_code gVideo_screen_init(void)
{
	if (!Visual.initialized) {
		int ret;

		/* Initialize a linked list to hold the visual objects. */
		ret = llist_init(&Visual.list);
		if (ret != 0) {
			critical("Failed to initialize visual linked list.");
			return GAME_RET_ERROR;
		}
	
		/* Create internal screen buffer. */
		Visual.screen_buffer = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);
		if (Visual.screen_buffer == NULL) {
			critical("Failed to create screen_buffer bitmap.");
			llist_destroy(&Visual.list);
			return GAME_RET_ERROR;
		}

		/* Set initialized flag so the video processing can go on. */
		Visual.initialized = true;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

void gVideo_screen_finish(void)
{
	if (Visual.initialized) {

		unsigned int i;
		unsigned int j;
		st_list_item *list_item = NULL;
		st_visual *elem = NULL;

		/* Free allocated bitmaps for list elements. */
		// TODO: this can be improved when we have a "get_next" function.
		debug(Gvideo_label, "Free visual elements bitmaps.");
		for (i = 0; i < Visual.list->item_counter; i++) {
			list_item = llist_get_item(Visual.list, i);
			if (list_item == NULL) {
				continue;
			}
			elem = (st_visual *)list_item->data;
			for (j = 0; j < GVIDEO_MAX_ELEM_BMP; j++) {
				if (elem->image[j] == NULL) {
					continue;
				}
				debug_screen("Will remove the bitmap %p...", elem->image[j]);
				destroy_bitmap(elem->image[j]);
				elem->image[j] = NULL;
			}
		}

		/* Free the linked list allocated memory. */
		debug(Gvideo_label, "Free visual list...");
		llist_destroy(&Visual.list);

		/* Free screen buffer bitmap. */
		debug(Gvideo_label, "Destroy visual buffer bitmap...");
		destroy_bitmap(Visual.screen_buffer);

		/* Reset the structure (also, the initialized flag is set to false). */
		memset(&Visual, 0, sizeof(Visual));
	}

	debug(Gvideo_label, "Game video screen sub-module has finished successfully.");
}

/**************************************************************************************************/

en_game_return_code gVideo_screen_update(void)
{
	CHECK_INITIALIZED(Visual.initialized);
	unsigned int i;
	st_visual *gvideo_elem = NULL;
	st_list_item *list_item= NULL;

	/* Clear the buffer so the images will not be overlapped. */
	clear(Visual.screen_buffer);

	/* Return if there is nothing to put into the screen. */
	if (Visual.list->item_counter == 0) {
		return GAME_RET_SUCCESS;
	}

	/* Draw scenery first layer. */
	debug_screen("Draw scenery bitmap.");
	list_item = llist_get_first(Visual.list);
	gvideo_elem = (st_visual *)list_item->data;
	debug_screen("scenery - bitmap %p.", gvideo_elem->image[gvideo_elem->img_index]);
	draw_sprite(Visual.screen_buffer, gvideo_elem->image[gvideo_elem->img_index], gvideo_elem->h, gvideo_elem->v);

	/* Iterate the visual list. Index 0 is the scenery. */
	for (i = 1; i < Visual.list->item_counter; i++) {
		debug_screen("Draw element at index %d.", i);
		list_item = llist_get_item(Visual.list, i);
		// TODO: improve this with a "get_next" function.
		if (list_item == NULL) {
			continue;
		}
		gvideo_elem = (st_visual *)list_item->data;
		debug_screen("index %d - bitmap %p.", i, gvideo_elem->image[gvideo_elem->img_index]);
		draw_sprite(Visual.screen_buffer, gvideo_elem->image[gvideo_elem->img_index], gvideo_elem->h, gvideo_elem->v);
		debug_screen("Element added into the screen. Type: %d.", gvideo_elem->type);
	}

	/* Draw all contet into the screen. */
	debug_screen("Draw buffer into screen.");
	draw_sprite(screen, Visual.screen_buffer, GVIDEO_SCREEN_ORIG_H, GVIDEO_SCREEN_ORIG_V);
	debug_screen("Screen update completed.");

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

int gVideo_screen_add_elem(st_visual *elem)
{
	CHECK_INITIALIZED(Visual.initialized);

	en_game_return_code ret;
	ret = gVideo_screen_check_elem(elem);
	if (ret != GAME_RET_SUCCESS) {
		debug(Gvideo_label, "The element solicited to be added contain invalid data.");
		return GAME_RET_ERROR;
	}

	st_list_item *item = NULL;

	/* Insert first item - the scenery figure. */
	if (Visual.list->item_counter == 0) {
		if ((elem->type == GVIDEO_VTYPE_SCEN_STATIC) ||
			 (elem->type == GVIDEO_VTYPE_SCEN_DYNAMIC)) {

			item = mixed_llist_add_elem(Visual.list, elem, sizeof(st_visual));
			if (item == NULL) {
				critical("Failed to add the first element into the visual list.");
				return GAME_RET_ERROR;
			}

			return item->index;
		}
		else {
			error("The first item to be added must be a scenery element.");
			return GAME_RET_ERROR;
		}
	}
	/* Insert item. */
	else {
		item = mixed_llist_add_elem(Visual.list, elem, sizeof(st_visual));
		if (item == NULL) {
			critical("Failed to add the first element into the visual list.");
			return GAME_RET_ERROR;
		}
		return item->index;
	}
}

/**************************************************************************************************/

en_game_return_code gVideo_screen_rem_elem(const unsigned int index)
{
	CHECK_INITIALIZED(Visual.initialized);

	st_list_item *elem = NULL;
	st_visual *v_elem = NULL;

	elem = mixed_llist_get_elem(Visual.list, index);
	if (elem == NULL) {
		error("The solicited element to be removed does not exists.");
		return GAME_RET_ERROR;
	}

	v_elem = (st_visual *) elem->data;

	destroy_bitmap(v_elem->image[v_elem->img_index]);
	mixed_llist_rem_elem(Visual.list, index);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gVideo_screen_update_elem_pos(st_visual *elem)
{
	CHECK_INITIALIZED(Visual.initialized);

	st_list_item *item;
	st_visual *list_elem;

	item = mixed_llist_get_elem(Visual.list, elem->key);
	if (item == NULL) {
		debug(Gvideo_label, "Failed to retrieve the element from the list.");
		return GAME_RET_ERROR;
	}

	list_elem = (st_visual *) item->data;

	/* TODO: This validation must be improved, because we are not considering the
	 * element size (if we put close to the bottom, the image could be out
	 * of the screen.
	 */
	/* Update element position. */
	if ((elem->h >= GVIDEO_SCREEN_ORIG_H) && (GAMESYSTEM_MAX_X > elem->h) &&
		(elem->v >= GVIDEO_SCREEN_ORIG_V) && (GAMESYSTEM_MAX_Y > elem->v)) {
		list_elem->h = elem->h;
		list_elem->v = elem->v;
	}

	if ((elem->img_index  > 0) && (elem->img_index < GVIDEO_MAX_ELEM_BMP)) {
		list_elem->img_index = elem->img_index;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gVideo_screen_update_elem_view(st_visual *elem)
{
	CHECK_INITIALIZED(Visual.initialized);

	/* Check if is a invalid index. */
	if (elem->img_index >= GVIDEO_MAX_ELEM_BMP) {
		return GAME_RET_ERROR;
	}

	st_list_item *item;
	st_visual *list_elem;

	item = mixed_llist_get_elem(Visual.list, elem->key);
	if (item == NULL) {
		debug(Gvideo_label, "Failed to retrieve the element from the list.");
		return GAME_RET_ERROR;
	}

	list_elem = (st_visual *) item->data;

	list_elem->img_index = elem->img_index;

	debug_screen("New element view: %d", elem->img_index);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gVideo_screen_check_elem(st_visual *elem)
{
	if ((elem->h < GVIDEO_SCREEN_ORIG_H) || (GAMESYSTEM_MAX_X < elem->h) ||
		(elem->v < GVIDEO_SCREEN_ORIG_V) || (GAMESYSTEM_MAX_Y < elem->v) ||
		(elem->type < 0) || (GVIDEO_VTYPE_MAX_ELEM <= elem->type) ||
		(elem->image == NULL)) {
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

