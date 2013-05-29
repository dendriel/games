#include <allegro.h>
#include <stdbool.h>

#include "linked_list.h"
#include "linked_listStructs.h"

#include "game_defines.h"
#include "game_structs.h"

#include "debug.h"
#include "macros.h"


/**************************************************************************************************/
/**
 *	\b Hold data used to process game screen issues.
 */
static struct Visual {
	bool initialized;	//!< Tells that the gameVideo_screen is initialized and could be used.
	st_list list;		//!< Visual List - Hold figures that will draw into the screen.
} visual = {false, {}};


/**************************************************************************************************/
/**
 *	\b Allocate data and copy the given element.
 *	\p dest Will have data allocated and receive the element pointed by orig.
 *	\p orig From where to copy data.
 *	\r GAME_RET_SUCCESS if cold copy the element; GAME_RET_ERROR otherwise.
 *	\n This function can be generic if we use void pointers and a parameter to inform data size.
 */
static en_game_return_code gameVideo_screen_copy_elem(st_list_item *item, st_visual *orig)
{
	if (!orig) {
		debug("Received invalid parameter.");
		return GAME_RET_ERROR;
	}

	st_visual *data;

	item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!item) {
		debug("Failed to allocate data for st_list_item.");
		return GAME_RET_ERROR;
	}

	data = (st_visual *)malloc(sizeof(st_visual));
	if (!data) {
		free(item);
		debug("Failed to allocate data for st_visual.");
		return GAME_RET_ERROR;
	}

	memcpy(data, orig, sizeof(st_visual));
	item->data = data;

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

void gameVideo_screen_init(void)
{
	if (!visual.initialized) {
		memset(&visual.list, 0, sizeof(visual.list));
		visual.initialized = true;
	}
}

/**************************************************************************************************/

en_game_return_code  gameVideo_screen_update(void)
{
	CHECK_INITIALIZED(visual.initialized);
	debug("updating screen!!");

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

en_game_return_code gameVideo_screen_add_elem(st_visual *elem)
{
	CHECK_INITIALIZED(visual.initialized);

	int ret;
	st_list_item *item = NULL;

	/* Insert first item - the scenery figure. */
	if ((visual.list.item_counter == 0) &&
		((elem->type == GAMEVIDEO_VTYPE_SCEN_STATIC) || (elem->type == GAMEVIDEO_VTYPE_SCEN_DYNAMIC))) {

		ret = gameVideo_screen_copy_elem(item, elem);
		if (ret != GAME_RET_SUCCESS) {
			return GAME_RET_ERROR;
		}

		ret = list_add_first(&visual.list, item);
		if (ret <= 0) {
			free(item->data);
			free(item);
			return GAME_RET_ERROR;
		}

		debug("Item with index %d was added to visual list.", item->index);
		return item->index;
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

