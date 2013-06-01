#ifndef GAMEVIDEO_SCREEN_HEADER
#define GAMEVIDEO_SCREEN_HEADER

#include "game_structs.h"
#include "game_defines.h"


/**************************************************************************************************/
/**
 *	\b Initialize the gameVideo_screen sub-module.
 */
en_game_return_code gameVideo_screen_init(void);

/**************************************************************************************************/
/**
 *	\b Finalize the gameVideo_screen sub-module and free the allocated resources.
 *	\n Also used to clear all the screen content, but must be re-initialized.
 */
void gameVideo_screen_finish(void);

/**************************************************************************************************/
/**
 *	\b Draw all the visual buffer content into the screen.
 *	\r GAME_RET_SUCCESS if the screen was successfuly updated;
 *	GAME_RET_UNITIALIZED if the screen sub-module was not initialized.
 */
en_game_return_code gameVideo_screen_update(void);

/**************************************************************************************************/
/**
 *	\b Add an element to the visual list that is inserted into the screen.
 *	\p elem The element to be added.
 *	\r If success, return the index of the element in the visual list; In case of error, returns
 *	GAME_RET_ERROR.
 */
int gameVideo_screen_add_elem(st_visual *elem);

/**************************************************************************************************/
/**
 *	\b Update the element position in the screen.
 *	\p elem Reference to the element that will be updated (and the new h,v values).
 *	\r GAME_RET_SUCCESS if could add the element; GAME_RET_ERROR if the element could not be 
 *	added to the list.
 */
en_game_return_code gameVideo_screen_update_elem_pos(st_visual *elem);

#endif /* GAMEVIDEO_SCREEN_HEADER */
