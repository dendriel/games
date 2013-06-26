#ifndef GSYSTEM_HEADER
#define GSYSTEM_HEADER

#include <pthread.h>
#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Main game system function. Initialize and controls the game itself.
 */
void gSystem_main(void);

/*************************************************************************************************/
/**
 *	\d Initialize the game brain module.
 *	\p thread_id Unused (here).
 *	\p mod_name Used as module label.
 *	\r GAMESYSTEM_RET_SUCCESS for successfuly execution.
 */
en_game_return_code gSystem_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE]);

#endif /* GSYSTEM_HEADER */
