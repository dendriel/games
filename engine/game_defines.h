#ifndef GAME_DEFINES_HEADER
#define GAME_DEFINES_HEADER

#include <mqueue.h>


#define GAME_MQUEUE_FAILED	(mqd_t)-1		//!< Mqueue error verification constant.

/**
 *	\b Return codes for general use.
 */
typedef enum {
	GAME_RET_SUCCESS	= 0,		//!< Generic success return code.
	GAME_RET_ERROR		= -1,			//!< Generic error return code.
} en_game_return_code;

/**
 *	\b Priority for message queues.
 */
typedef enum {
	GAME_MQUEUE_PRIO_0 = 0,		//!< Used for critical messages, as media and system issues.
	GAME_MQUEUE_PRIO_1 = 1,		//!< Reserved.
	GAME_MQUEUE_PRIO_2 = 2,		//!< Default mqueue priority.
} en_game_mqueue_prio;

/**
 *	\b Define possible actions to be requested in a message.
 */
typedef enum {
	GAME_UPDATE_SCREEN = 1234		//!< GAMEVIDEO_QUEUE_NAME.
} en_game_msg_type;

#endif /* GAME_DEFINES_HEADER*/
