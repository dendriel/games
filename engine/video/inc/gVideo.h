#ifndef GVIDEO_HEADER
#define GVIDEO_HEADER

#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\d Initialize the game video module.
 *	\p thread_id A reference to the thread to future thread return (join).
 *	\r GAMESYSTEM_RET_SUCCESS for successfuly execution;
 *	GAMESYSTEM_RET_ERROR for error in the execution.
 */
en_game_return_code gameVideo_init(pthread_t *thread_id);

#endif /* GVIDEO_HEADER */
