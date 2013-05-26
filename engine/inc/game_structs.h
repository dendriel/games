#ifndef GAMESTRUCTS_HEADER
#define GAMESTRUCTS_HEADER

#include "game_defines.h"

/**
 * \b Default message structure to be exchanged across the system threads.
 */
typedef struct {
	en_game_msg_type type;		//!< The type of the message (used to knows how to unpack).
	en_game_mod_id id;			//!< Identifier of message owner module.
} st_game_msg;

#endif /* GAMESTRUCTS_HEADER */
