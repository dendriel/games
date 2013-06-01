#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#include "mixedAPI.h"
#include "mixedAPI_defines.h"
#include "llist.h"
#include "llist_structs.h"
#include "llist_defines.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\b Allocate data and copy the given element.
 *	\p dest Will have data allocated and receive the element pointed by orig.
 *	\p orig From where to copy data.
 *	\r GAME_RET_SUCCESS if cold copy the element; MIXED_RET_ERROR otherwise.
 *	\n This function can be generic if we use void pointers and a parameter to inform data size.
 */
static en_mixed_return_code mixed_llist_copy_elem(st_list_item **item, const void *elem, const size_t elem_size);


/**************************************************************************************************/

en_mixed_return_code mixed_create_mqueue(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode)
{

	/* Remove the mqueue if it is already created (removing previous messages). */
	(void) mq_unlink(mq_name);

	return mixed_open_mqueue(mqueue, mq_name, mq_size, mq_mode);
}

/**************************************************************************************************/

en_mixed_return_code mixed_open_mqueue(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode)
{
	struct mq_attr attr;

	if (!mqueue || !mq_name) {
		return MIXED_RET_ERROR;
	}

	/* Initialize the queue attributes */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = MIXED_MAX_MQUEUE_MSG;
	attr.mq_msgsize = mq_size;

	/* Create the message queue. */
	*mqueue = mq_open(mq_name, mq_mode, 0644, &attr);
	if (*mqueue == (mqd_t)-1) {
		debug("Failed to open mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

void mixed_close_mqueue_sender(const mqd_t *mqueue, const char *mq_name)
{
	int ret;

	ret = mq_close(*mqueue);
	if (ret != 0) {
		debug("Failed to close the mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
	}
}

/**************************************************************************************************/

void mixed_close_mqueue(const mqd_t *mqueue, const char *mq_name)
{
	int ret;

	mixed_close_mqueue_sender(mqueue, mq_name);

	ret = mq_unlink(mq_name);
	if (ret != 0 && (errno != 2)) {
		debug("Failed to unlink the mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
	}
}

/**************************************************************************************************/

en_mixed_return_code mixed_list_create(st_list *list)
{
	list = (st_list *)malloc(sizeof(st_list));
	if (!list) {
		debug("Failed to allocate memory for st_list.\n");
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

st_list_item *mixed_llist_add_first(st_list *list, const void *elem, const size_t elem_size)
{
	int ret;
	en_mixed_return_code mret;
	st_list_item *item = NULL;

	if (!list || !elem) {
		debug("Null parameter received.\n");
		return NULL;
	}

	mret = mixed_llist_copy_elem(&item, elem, elem_size);
	if (mret != MIXED_RET_SUCCESS) {
		debug("Failed to copy element to the linked list.\n");
		return NULL;
	}

	ret = llist_add_first(list, item);
	if (ret != MIXED_RET_SUCCESS) {
		debug("Failed to add the first element into the list.\n");
		return NULL;
	}

	return item;
}

/**************************************************************************************************/

en_mixed_return_code mixed_llist_add_elem(st_list *list, void *elem)
{
	int ret;
	st_list_item *list_item = NULL;

	if (!list || !elem) {
		debug("Null parameter received.");
		return MIXED_RET_ERROR;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		debug("Failed to allocate memory for st_list_item.");
		return MIXED_RET_ERROR;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = elem;

	ret = llist_add_next(list, list_item);
	if (ret != 0) {
		debug("Failed to add element to list.");
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

static en_mixed_return_code mixed_llist_copy_elem(st_list_item **item, const void *elem, const size_t elem_size)
{
	if (!elem || !item) {
		debug("Received invalid parameter.");
		return MIXED_RET_ERROR;
	}

	void *data = NULL;

	*item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!item) {
		debug("Failed to allocate data for st_list_item.");
		return MIXED_RET_ERROR;
	}

	data = (void *)malloc(elem_size);
	if (!data) {
		free(item);
		debug("Failed to allocate data for the element.");
		return MIXED_RET_ERROR;
	}

	memcpy(data, elem, elem_size);
	(*item)->data = data;

	return MIXED_RET_SUCCESS;
}

