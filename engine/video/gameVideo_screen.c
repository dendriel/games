#include <allegro.h>
#include <stdbool.h>

#include "gameVideo_screen.h"
#include "gameVideo_screen_defines.h"
#include "game_defines.h"
#include "game_structs.h"
#include "gameSystem_defines.h"

#include "llist.h"
#include "llist_defines.h"
#include "llist_structs.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Hold data used to process game screen issues.
 */
static struct Visual {
	bool initialized;	//!< Tells that the gameVideo_screen is initialized and could be used.
	st_list *list;		//!< Visual List - Hold figures that will draw into the screen.
} visual = {false, NULL};


// Put inside the structure.
	BITMAP *gvideo_buffer = NULL;


/**************************************************************************************************/

en_game_return_code gameVideo_screen_init(void)
{
	if (!visual.initialized) {
		int ret;

		ret = llist_init(&visual.list);
		if (ret != 0) {
			return GAME_RET_ERROR;
		}

		visual.initialized = true;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

void gameVideo_screen_finish(void)
{
	if (visual.initialized) {

		unsigned int i;
		st_list_item *list_item = NULL;
		st_visual *elem = NULL;

		/* Free allocated bitmaps for elements. */
		for(i = 0; i < visual.list->item_counter; i++) {
			list_item = llist_get_item(visual.list, i);
			elem = (st_visual *)list_item->data;
			destroy_bitmap(elem->image);
		}

		// TODO: this linked list kind sucks... as the own description tells "study purpose, only" :[
		//llist_destroy(&visual.list);
	}
}

/**************************************************************************************************/

en_game_return_code gameVideo_screen_update(void)
{
	CHECK_INITIALIZED(visual.initialized);
	unsigned int i;
	st_visual *gvideo_elem = NULL;
	st_list_item *list_item= NULL;

	// maybe will be used.
	//clear_buffer(gvideo_buffer);

	/* Return if there is nothing to put into the screen. */
	if (visual.list->item_counter == 0) {
		return GAME_RET_SUCCESS;
	}
	/* Create internal screen buffer. */
	gvideo_buffer = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);

	/* Draw scenery first layer. */
	list_item = llist_get_first(visual.list);
	gvideo_elem = (st_visual *)list_item->data;
	draw_sprite(gvideo_buffer, gvideo_elem->image, gvideo_elem->h, gvideo_elem->v);

	/* Iterate the visual list. Index 0 is the scenery. */
	for (i = 1; i < visual.list->item_counter; i++) {
		gvideo_elem = (st_visual *)llist_get_item(visual.list, i);
		draw_sprite(gvideo_buffer, gvideo_elem->image, gvideo_elem->h, gvideo_elem->v);
		debug("Element added into the screen. Type: %d.", gvideo_elem->type);
	}

	/* Draw all contet into the screen. */
	draw_sprite(screen, gvideo_buffer, GAMEVIDEO_SCREEN_ORIG_H, GAMEVIDEO_SCREEN_ORIG_V);

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gameVideo_screen_add_elem(st_visual *elem)
{
	CHECK_INITIALIZED(visual.initialized);

	st_list_item *item = NULL;

	/* Insert first item - the scenery figure. */
	if ((elem->type == GAMEVIDEO_VTYPE_SCEN_STATIC) || (elem->type == GAMEVIDEO_VTYPE_SCEN_DYNAMIC)) {
		if (visual.list->item_counter == 0) {

			item = mixed_llist_add_first(visual.list, elem, sizeof(st_visual));
			if (item == NULL) {
				critical("Failed to add the first element into the visual list.");
				return GAME_RET_ERROR;
			}

			debug("Item with index %d was added to visual list.", item->index);
			return 0;
		}
		else {
			debug("Error. One scenery can be loaded per time.");
			return GAME_RET_ERROR;
		}
	}
	/* Insert item. */
	else {
		debug("insert item!");
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gameVideo_screen_update_elem(st_visual *elem)
{
	CHECK_INITIALIZED(visual.initialized);


	return GAME_RET_SUCCESS;
}

