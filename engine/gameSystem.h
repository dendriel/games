#ifndef GAMESYSTEM_HEADER
#define GAMESYSTEM_HEADER

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Main game system function. Initialize the game itself.
 */
void gameSystem_main(void);

/*************************************************************************************************/
/**
 *	\d Initialize the allegro library and install components (keyboard, mouse)
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
game_return_code gameSystem_engine_init(void);

/*************************************************************************************************/
/**
 *	\d Initialize the media components (audio, video).
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
game_return_code gameSystem_media_init(void);

/*************************************************************************************************/
/**
 *	\d Halt the game engine.
 */
void gameSystem_engine_exit(void);

#endif /* GAMESYSTEM_HEADER */
