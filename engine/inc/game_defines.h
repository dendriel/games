#ifndef GAME_DEFINES_HEADER
#define GAME_DEFINES_HEADER

#include <mqueue.h>


#define GAME_MQUEUE_FAILED			(mqd_t)-1				//!< Mqueue error verification constant.
#define GAME_MQUEUE_SEND_MODE		(O_CREAT|O_WRONLY)		//!< Open mqueue in send (write) mode.
#define GAME_MQUEUE_CRRECV_MODE		(O_CREAT|O_RDONLY)		//!< Create mqueue in recv (read) mode.
#define GAME_MQUEUE_RECV_MODE		(O_RDONLY)				//!< Open mqueue in recv (read) mode.
#define GAME_MQUEUE_SIZE			1024					//!< Message size to be received from a mqueue.
#define GAME_MQUEUE_RECV_BUF_SIZE	GAME_MQUEUE_SIZE+1		//!< Receive buffer size.
#define GAME_MOD_LABEL_SIZE			32						//!< Module label maximum string size.

/**
 *	\b Return codes for general use.
 */
typedef enum {
	GAME_RET_HALT			= 1,		//!< Informs that the process must finish (used in process message functions).
	GAME_RET_SUCCESS		= 0,		//!< Generic success return code.
	GAME_RET_ERROR			= -1,		//!< Generic error return code.
	GAME_RET_UNINITIALIZED	= -2,		//!< Uninitialized module.
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
 *	\b Used to identify sender of the messages between modules.
 */
typedef enum {
	GSYSTEM_MOD_ID = 100,		//!< Game system [main] module identifier.
	GBRAIN_MOD_ID,				//!< Game brain module identifier.
	GVIDEO_MOD_ID,				//!< Game video module identifier.
	GCONTROLLER_MOD_ID,			//!< Game controller module identifier.
} en_game_mod_id;

/**
 *	\b Define possible actions to be requested in a message.
 */
typedef enum {
	/* System general actions. */
	GAME_ACTION_HALT_MODULE = 1,		//!< Requests to the module to terminate and free his resources.
	/* Screen related actions. */
	GAME_ACTION_UPDATE_SCREEN,			//!< Requests to the game video module to update the screen.
	GAME_ACTION_ADD_SCREEN_ELEM,		//!< Requests to the game video module to add a new element into the screen.
	GAME_ACTION_REM_SCREEN_ELEM,		//!< Requests to the game video module to remove an element from the screen.
	GAME_ACTION_UPD_SCREEN_ELEM,		//!< Requests to the game video module to update the element (position; image style).
	GAME_ACTION_UPD_SCREEN_ELEM_POS,	//!< Requests to the game video module to update the element (position; image style).
	GAME_ACTION_UPD_SCREEN_ELEM_VIEW,	//!< Requests to the game video module to update the element (position; image style).
	GAME_ACTION_RET_SCREEN_ELEM,		//!< Used to send the result of the screen elements related requests.
	/* Scenery related actions. */
	GAME_ACTION_LOAD_SCENERY,			//!< Requests to the game brain module to load the given scenery and his elements.
	/* Controller related actions. */
	GAME_ACTION_MOVE_UP,				//!< Requests to the game brain to move up (the player character).
	GAME_ACTION_MOVE_RIGHT,				//!< Requests to the game brain to move right (the player character).
	GAME_ACTION_MOVE_DOWN,				//!< Requests to the game brain to move down (the player character).
	GAME_ACTION_MOVE_LEFT,				//!< Requests to the game brain to move left (the player character).
	GAME_ACTION_MISC_EXIT,				//!< Requests to exit the game.
} en_game_msg_type;

/**
 *	\b Define possible answers to request messages.
 */
typedef enum {
	GAME_MSG_RET_OP_SUCCESS = 100,			//!< The operation was successful executed and the structure has valid values.
	GAME_MSG_RET_OP_FAILED,					//!< The operation was failed and the structure data is invalid to be used.
	GAME_MSG_RET_ELEM_INVALID,				//!< Requested element is invalid.
	GAME_MSG_RET_ELEM_NOTFOUND,				//!< Requested element was not found.
} en_game_msg_ret;


#endif /* GAME_DEFINES_HEADER*/
