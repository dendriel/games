#ifndef GSYSTEM_HEADER
#define GSYSTEM_HEADER

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Main game system function. Initialize the game itself.
 */
void gSystem_main(void);

/*************************************************************************************************/
/**
 *	\d Initialize the allegro library and install components (keyboard, mouse)
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
en_game_return_code gSystem_engine_init(void);

/*************************************************************************************************/
/**
 *	\d Initialize the media components (audio, video).
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
en_game_return_code gSystem_media_init(void);

/*************************************************************************************************/
/**
 *	\d Halt the game engine.
 */
void gSystem_engine_exit(void);

#endif /* GSYSTEM_HEADER */
