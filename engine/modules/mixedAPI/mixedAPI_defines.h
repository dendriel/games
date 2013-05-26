#ifndef MIDEXAPI_DEFINES_HEADER
#define MIDEXAPI_DEFINES_HEADER

#define MIXED_MAX_MQUEUE_MSG	1024	//!< Define maximun number of enqueued messages.

/**
 *	\b Define return codes for mixed API.
 */
typedef enum {
	MIXED_RET_SUCCESS	= 0,	//!< Generic success return code.
	MIXED_RET_ERROR		= -1,	//!< Generic error return code.
} en_mixed_return_code;

#endif /* MIDEXAPI_DEFINES_HEADER */
