#ifndef GAMESTRUCTS_HEADER
#define GAMESTRUCTS_HEADER

#include "game_defines.h"

/**
 * \b Default message structure to be exchanged across the system threads.
 */
typedef struct {
	en_game_action action;
} st_game_msg;

#endif /* GAMESTRUCTS_HEADER */
