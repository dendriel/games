#ifndef GBRAIN_VIDEO_INTF_HEADER
#define GBRAIN_VIDEO_INTF_HEADER

#include "game_defines.h"
#include "gameVideo_structs.h"

// testing purpose only!
en_game_return_code gBrain_video_intf_test();

/**
 *	\b Requests to the gameVideo module to add an element into the screen.
 *	\p v_eleme The element to be added.
 *	\r GAME_RET_SUCCESS if could add the element; GAME_RET_ERROR otherwise.
 */
en_game_return_code gBrain_video_intf_add_elem(st_visual *v_elem);

#endif /* GBRAIN_VIDEO_INTF_HEADER */
