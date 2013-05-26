#ifndef MIXEDAPI_HEADER
#define MIXEDAPI_HEADER

#include <mqueue.h>
#include "mixedAPI_defines.h"

/**************************************************************************************************/
/**
 *	\b Interface function to open a mqueue.
 *	\p gvideo_mqueue Used to hold the mqueue reference.
 *	\p mq_name The name of the mqueue to be opened.
 *	\r MIXED_RET_SUCCESS if could open the mqueue; MIXED_RET_ERROR otherwise.
 */
en_mixed_return_code mixed_open_mqueue(mqd_t *mqueue, const char *mq_name, const unsigned mq_size);

/**************************************************************************************************/
/**
 *	\b Interface function to close and unlink a mqueue.
 *	\p gvideo_mqueue Reference to the mqueue that will be closed.
 *	\p mq_name The name of the mqueue to be closed.
 */
void mixed_close_mqueue(const mqd_t *mqueue, const char *mq_name);

#endif /* MIXEDAPI_HEADER */
