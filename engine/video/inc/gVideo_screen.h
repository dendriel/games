#ifndef GVIDEO_SCREEN_HEADER
#define GVIDEO_SCREEN_HEADER

#include "game_structs.h"
#include "game_defines.h"


/**************************************************************************************************/
/**
 *	\b Initialize the game video screen sub-module.
 */
en_game_return_code gVideo_screen_init(void);

/**************************************************************************************************/
/**
 *	\b Finalize the game video screen sub-module and free the allocated resources.
 *	\n Also used to clear all the screen content, but must be re-initialized.
 */
void gVideo_screen_finish(void);

/**************************************************************************************************/
/**
 *	\b Draw all the visual buffer content into the screen.
 *	\r GAME_RET_SUCCESS if the screen was successfuly updated;
 *	GAME_RET_UNITIALIZED if the screen sub-module was not initialized.
 */
en_game_return_code gVideo_screen_update(void);

/**************************************************************************************************/
/**
 *	\b Add an element to the visual list that is inserted into the screen.
 *	\p elem The element to be added.
 *	\r If success, return the index of the element in the visual list; In case of error, returns
 *	GAME_RET_ERROR.
 *	\n TODO: return index as output parameter.
 */
int gVideo_screen_add_elem(st_visual *elem);

/**************************************************************************************************/
/**
 *	\b Remove the element pointed by index from the visual linked list.
 *	\p index Reference to the element that will be removed.
 *	\r GAME_RET_SUCCESS if the element was removed; GAME_RET_ERROR if the element was not found.
 */
en_game_return_code gVideo_screen_rem_elem(const unsigned int index);

/**************************************************************************************************/
/**
 *	\b Update the element in the screen.
 *	\p elem Reference to the element that will be updated (and the new h,v values).
 *	\r GAME_RET_SUCCESS if could update the element; GAME_RET_ERROR otherwise.
 */
en_game_return_code gVideo_screen_update_elem_pos(st_visual *elem);

#endif /* GVIDEO_SCREEN_HEADER */
