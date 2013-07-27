#ifndef GVIDEO_HEADER
#define GVIDEO_HEADER

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Initialize the game video module.
 *	\p thread_id A reference to the thread to future thread return (join).
 *	\p mod_name Used as module label.
 *	\r GAMESYSTEM_RET_SUCCESS for successfuly execution;
 *	GAMESYSTEM_RET_ERROR for error in the execution.
 */
en_game_return_code gVideo_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE]);

#endif /* GVIDEO_HEADER */
