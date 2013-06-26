#ifndef MIDEXAPI_DEFINES_HEADER
#define MIDEXAPI_DEFINES_HEADER

#define MIXED_MAX_MQUEUE_MSG	10			//!< Define maximun number of enqueued messages.
#define MIXED_MQUEUE_SIZE		1024		//!< Message size to be received from a mqueue.
#define MIXED_MQUEUE_SEND_MODE	O_WRONLY	//!< Open mqueue in send (write) mode.

/**
 *	\b Define return codes for mixed API.
 */
typedef enum {
	MIXED_RET_SUCCESS	= 0,	//!< Generic success return code.
	MIXED_RET_ERROR		= -1,	//!< Generic error return code.
	MIXED_RET_TIMEOUT	= -2,	//!< Returned by timeout.
} en_mixed_return_code;

#endif /* MIDEXAPI_DEFINES_HEADER */
