#ifndef GCONTROLLER_HEADER
#define GCONTROLLER_HEADER

#include "pthread.h"

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Initialize the game controller module.
 *	\p thread_id A reference to the thread to future thread return (join).
 *	\r GAMESYSTEM_RET_SUCCESS for successfuly execution;
 *	GAMESYSTEM_RET_ERROR for error in the execution.
 */
en_game_return_code gController_init(pthread_t *thread_id);

#endif /* GCONTROLLER_HEADER */
