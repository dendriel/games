#ifndef GBRAIN_GVIDEO_INTF_HEADER
#define GBRAIN_GVIDEO_INTF_HEADER

#include "game_defines.h"

#include "gBrain_structs.h"
#include "gVideo_structs.h"

#include "llist_structs.h"

/**************************************************************************************************/
/**
 *	\b Add the given element to the scenery elements list and request to the game video module to 
 *	add a visual element in the visual list (that will be put in the screen).
 *	\p elem The element data to be added into the list.
 *	\p elem_list The list that will received the element.
 *	\p elem_index Output parameter. The index of the element in the Scenery list.
 *	\r The element index if could add the element both Scenery and Visual list;
 *	GAME_RET_ERROR if something went wrong and the element was not added.
 */
en_game_return_code gBrain_gvideo_intf_add_elem(
	st_scen_elem *elem,
	st_list *elem_list,
	unsigned int *elem_index);

/**************************************************************************************************/
/**
 *	\b Remove the given element from both Scenery and Visual list.
 *	\p index The element index into the Scenery elements list.
 *	\p elem_list The list that will have the element removed.
 *	\r GAME_RET_SUCCESS if could remove the element from the lists.
 */
en_game_return_code gBrain_gvideo_intf_rem_elem(const unsigned int index, st_list *elem_list);

/**************************************************************************************************/
/**
 *	\b Update the element pointed by index with new coordinations.
 *	\p elem_index A reference to the element that will be updated.
 *	\p img_index What view of the element will be showed.
 *	\p h New horizontal coordination (fill with GVIDEO_EMPTY data if want to not updated).
 *	\p v New vertical coordination (fill with GVIDEO_EMPTY data if want to not updated).
 *	\p elem_list The list that will have the element updated.
 *	\r GAME_RET_SUCCESS if the element was updated; GAME_RET_HALT if received a halt solicitation
 *	while updating the element; GAME_RET_ERROR if the element could not be updated.
 */
en_game_return_code gBrain_gvideo_intf_upd_elem(
	const unsigned int elem_index,
	const unsigned int img_index,
	const unsigned int h,
	const unsigned int v,
	st_list *elem_list);

#endif /* GBRAIN_GVIDEO_INTF_HEADER */
