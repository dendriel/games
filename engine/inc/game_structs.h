#ifndef GAMESTRUCTS_HEADER
#define GAMESTRUCTS_HEADER

#include "gVideo_structs.h"
#include "gBrain_structs.h"
#include "game_defines.h"

/**
 * \b Default message structure to be exchanged across the system threads.
 */
typedef struct {
	union {
		st_visual v_elem;		//!< Used to send requests to game video module.
		st_scen_elem sc_elem;	//!< Unused here, so far.
	};
	en_game_msg_type type;		//!< The type of the message (used to knows how to unpack).
	en_game_mod_id id;			//!< Identifier of message owner module.
	en_game_msg_ret reply;		//!< Operation excution status (filled by the receiver).
} st_game_msg;

#endif /* GAMESTRUCTS_HEADER */
