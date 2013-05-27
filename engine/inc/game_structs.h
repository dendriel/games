#ifndef GAMESTRUCTS_HEADER
#define GAMESTRUCTS_HEADER

#include "gameVideo_structs.h"
#include "game_defines.h"

#define GAME_MQUEUE_SIZE	sizeof(st_game_msg)			//!< Message size to be received from a mqueue.
#define GAME_MQUEUE_SEND_SIZE	sizeof(st_game_msg)+1		//!< Message size to be sent through a mqueue.

/**
 * \b Default message structure to be exchanged across the system threads.
 */
typedef struct {
	union Data {
		st_visual v_element;
	} data;
	en_game_msg_type type;		//!< The type of the message (used to knows how to unpack).
	en_game_mod_id id;			//!< Identifier of message owner module.
} st_game_msg;

#endif /* GAMESTRUCTS_HEADER */
