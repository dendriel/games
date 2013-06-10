#ifndef GBRAIN_HEADER
#define GBRAIN_HEADER

#include "pthread.h"

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Initialize the game brain module.
 *	\p thread_id A reference to the thread to future thread return (join).
 *	\p mod_name Used as module label.
 *	\r GAMESYSTEM_RET_SUCCESS for successfuly execution;
 *	GAMESYSTEM_RET_ERROR for error in the execution.
 */
en_game_return_code gBrain_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE]);

#endif /* GBRAIN_HEADER */
