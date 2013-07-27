#ifndef MIXEDAPI_HEADER
#define MIXEDAPI_HEADER

#include <mqueue.h>
#include <stdbool.h>
#include "llist_structs.h"
#include "mixedAPI_defines.h"


/**************************************************************************************************/
/**
 *	\b Open a mqueue and send a generic (void *) message thorugh.
 *	\p mqueue_name The mqueue that will be opened.
 *	\p msg_prio The priority of the message that will be sent.
 *	\p msg The data to be sent.
 *	\r MIXED_RET_SUCCESS for successfully operation; MIXED_RET_ERROR otherwise.
 */
en_mixed_return_code mixed_mqueue_send(
const char *mqueue_name,
const unsigned int msg_prio,
const void *msg);

/**************************************************************************************************/
/**
 *	\b Receive a message through a mqueue (the mqueue must be already openned). If tout_sec or 
 *	tout_usec is set, 'mqueuetimedreceive' will be used and touc_sec and touc_used will be used to 
 *	fill the tmespec structure.
 *	\p mqueue_name The mqueue to receive the message.
 *	\p rcvd_data A buffer to store the received data.
 *	\p data_size The size of the parameter "buffer".
 *	\p tout_sec Timeout in seconds.
 *	\p tout_nsec Timeout in nano-seconds.
 *	\r GAME_RET_SUCCESS if could successfully receive the data; GAME_RET_TIMEOUT if the receive 
 *	operation has canceled by the timeout; GAME_RET_ERROR for generic operation error.
 */
en_mixed_return_code mixed_mqueue_recv(
const mqd_t mqueue,
char *recvd_data,
const size_t data_size,
const float tout_sec,
const long tout_nsec);

/**************************************************************************************************/
/**
 *	\b Does the same as "mixed_open_mqueue", expect that destroys the [mq_name] if it already 
 *	exists. Should be used by the holders (receptors) of the [mq_name].
 *	\p mqueue used to hold the mqueue reference.
 *	\p mq_name the name of the mqueue to be opened.
 *	\p mq_size size of the messages to send/receive through the mqueue.
 *	\p mq_mode the mqueue operation mode.
 *	\r mixed_ret_success if could open the mqueue; mixed_ret_error otherwise.
 */
en_mixed_return_code mixed_mqueue_create(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode);

/**************************************************************************************************/
/**
 *	\b interface function to open a mqueue.
 *	\p mqueue used to hold the mqueue reference.
 *	\p mq_name the name of the mqueue to be opened.
 *	\p mq_size size of the messages to send/receive through the mqueue.
 *	\p mq_mode the mqueue operation mode.
 *	\r mixed_ret_success if could open the mqueue; mixed_ret_error otherwise.
 */
en_mixed_return_code mixed_mqueue_open(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode);

/**************************************************************************************************/
/**
 *	\b Interface function to close a mqueue opened just to send a message.
 *	\p gvideo_mqueue Reference to the mqueue that will be closed.
 *	\p mq_name The name of the mqueue to be closed.
 */
void mixed_mqueue_close_sender(const mqd_t *mqueue, const char *mq_name);

/**************************************************************************************************/
/**
 *	\b Interface function to close [and unlink] a mqueue.
 *	\p gvideo_mqueue Reference to the mqueue that will be closed.
 *	\p mq_name The name of the mqueue to be closed.
 */
void mixed_mqueue_close(const mqd_t *mqueue, const char *mq_name);

/**************************************************************************************************/
/**
 *	\d Insert an element in the list.
 *	\p list Reference to the list that will receive the element.
 *	\p elem The element to be inserted.
 *	\p elem_size The size of the elemen to be inserted.
 *	\r Will return the inserted item or NULL in case of operation error.
 */
st_list_item *mixed_llist_add_elem(
st_list *list,
const void *elem,
const size_t elem_size);

/**************************************************************************************************/
/**
 *	\b Remove from the list the element pointed by index.
 *	\p list The linked list that will have the element removed.
 *	\p index A reference for the element to be removed.
 */
void mixed_llist_rem_elem(st_list *list, const unsigned int index);

/**************************************************************************************************/
/**
 *	\b Retrieve (just get) from list the item pointed by index.
 *	\p list The linked list to be searched for.
 *	\p index A reference for the requested item.
 *	\r The element if the list and index are valid; NULL otherwise.
 */
st_list_item *mixed_llist_get_elem(st_list *list, const unsigned int index);

#endif /* MIXEDAPI_HEADER */
