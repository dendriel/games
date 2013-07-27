#ifndef GBRAIN_SCENERY_HEADER
#define GBRAIN_SCENERY_HEADER

#include "game_defines.h"


/*************************************************************************************************/
/**
 *	\b Initialize the game brain scenery sub-module.
 */
en_game_return_code gBrain_scenery_init(void);

/**************************************************************************************************/
/**
 *	\b Finalize the game brain scenery sub-module and free the allocated resources.
 *	\n Do not free the visual elements bitmaps here! The game video scree sub-module should take 
 *	care of this.
 */
void gBrain_scenery_finish(void);

/*************************************************************************************************/
/**
 *	\b Load a scenery and all his issues.
 *	\r GAME_RET_SUCCESS if the scenery could be sucessfully loaded; GAME_RET_ERROR if something 
 *	went wrong.
 */
en_game_return_code gBrain_scenery_load(void);

#endif /* GBRAIN_SCENERY_HEADER */
