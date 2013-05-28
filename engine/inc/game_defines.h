#ifndef GAME_DEFINES_HEADER
#define GAME_DEFINES_HEADER

#include <mqueue.h>


#define GAME_MQUEUE_FAILED		(mqd_t)-1				//!< Mqueue error verification constant.
#define GAME_MQUEUE_SEND_MODE	(O_CREAT|O_WRONLY)		//!< Open mqueue in send (write) mode.
#define GAME_MQUEUE_RECV_MODE	(O_CREAT|O_RDONLY)		//!< Open mqueue in recv (read) mode.

/**
 *	\b Return codes for general use.
 */
typedef enum {
	GAME_RET_HALT		= 1,		//!< Informs that the process must finish (used in process message functions).
	GAME_RET_SUCCESS	= 0,		//!< Generic success return code.
	GAME_RET_ERROR		= -1,		//!< Generic error return code.
} en_game_return_code;

/**
 *	\b Priority for message queues.
 */
typedef enum {
	GAME_MQUEUE_PRIO_0 = 0,		//!< Used for critical messages.
	GAME_MQUEUE_PRIO_1 = 1,		//!< Used for media issues.
	GAME_MQUEUE_PRIO_2 = 2,		//!< Default mqueue priority.
} en_game_mqueue_prio;

/**
 *	\b Define possible actions to be requested in a message.
 */
typedef enum {
	GAME_ACTION_HALT_MODULE = 1,		//!< Requests to the module to terminate and free his resources.
	GAME_ACTION_UPDATE_SCREEN,			//!< Requests to the gameVideo module to update the screen.
	GAME_ACTION_ADD_SCREEN_ELEM,		//!< Requests to the gameVideo module to add a new element into the screen.
} en_game_msg_type;

/**
 *	\b Used to identify sender of the messages between modules.
 */
typedef enum {
	GAMESYSTEM_MOD_ID = 100,		//!< Game system [main] module identifier.
	GAMEBRAIN_MOD_ID,				//!< Game brain module identifier.
	GAMEVIDEO_MOD_ID,				//!< Game video module identifier.
} en_game_mod_id;

#endif /* GAME_DEFINES_HEADER*/
