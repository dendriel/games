#ifndef MIXEDAPI_HEADER
#define MIXEDAPI_HEADER

#include <mqueue.h>
#include "linked_listStructs.h"
#include "mixedAPI_defines.h"

/**************************************************************************************************/
/**
 *	\b Interface function to open a mqueue.
 *	\p mqueue Used to hold the mqueue reference.
 *	\p mq_name The name of the mqueue to be opened.
 *	\p mq_size Size of the messages to send/receive through the mqueue.
 *	\p mq_mode The mqueue operation mode.
 *	\r MIXED_RET_SUCCESS if could open the mqueue; MIXED_RET_ERROR otherwise.
 */
en_mixed_return_code mixed_open_mqueue(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode);

/**************************************************************************************************/
/**
 *	\b Interface function to close and unlink a mqueue.
 *	\p gvideo_mqueue Reference to the mqueue that will be closed.
 *	\p mq_name The name of the mqueue to be closed.
 */
void mixed_close_mqueue(const mqd_t *mqueue, const char *mq_name);

/**************************************************************************************************/
/**
 *	\b Allocate memory for the visual list.
 *	\p list Reference to the visual list.
 *	\r MIXED_RET_SUCCESS for correctly list creation;
 *	MIXED_RET_ERROR if could not create the list.
 */
en_mixed_return_code mixed_list_create(st_list *list);

/**************************************************************************************************/
/**
 *	\d Insert the first element in the list.
 *	\p list Reference to the list that will receive the element.
 *	\p elem The element to be inserted.
 *	\r MIXED_RET_SUCCESS for correctly operation; MIXED_RET_ERROR otherwise.
 */
en_mixed_return_code mixed_visual_list_add_first_elem(st_list *list, void *elem);

/**************************************************************************************************/
/**
 *	\d Insert an element in the list.
 *	\p list Reference to the list that will receive the element.
 *	\p elem The element to be inserted.
 *	\r MIXED_RET_SUCCESS for correctly operation; MIXED_RET_ERROR otherwise.
 */
en_mixed_return_code mixed_visual_list_add_elem(st_list *list, void *elem);

#endif /* MIXEDAPI_HEADER */
