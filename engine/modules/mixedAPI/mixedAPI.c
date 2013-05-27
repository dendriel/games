#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#include "linked_list.h"
#include "linked_listStructs.h"
#include "mixedAPI.h"
#include "mixedAPI_defines.h"


/**************************************************************************************************/

en_mixed_return_code mixed_open_mqueue(
mqd_t *mqueue,
const char *mq_name,
const unsigned mq_size,
const mode_t mq_mode)
{
	struct mq_attr attr;

	if (!mqueue) {
		return MIXED_RET_ERROR;
	}

	/* Initialize the queue attributes */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = MIXED_MAX_MQUEUE_MSG;
	attr.mq_msgsize = mq_size;

	/* Create the message queue. */
	*mqueue = mq_open(mq_name, mq_mode, 0644, &attr);
	if (*mqueue == (mqd_t)-1) {
		fprintf(stderr, "Failed to open mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

void mixed_close_mqueue(const mqd_t *mqueue, const char *mq_name)
{
	int ret;

	ret = mq_close(*mqueue);
	if (ret != 0) {
		fprintf(stderr, "Failed to close the mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
	}

if (0) {
	/* This action is not worling very well right now. */
	ret = mq_unlink(mq_name);
	if (ret != 0) {
		fprintf(stderr, "Failed to unlink the mqueue. name: %s; errno: %d; msg: %s\n",
			mq_name, errno, strerror(errno));
	}
}

}

/**************************************************************************************************/

en_mixed_return_code mixed_list_create(st_list *list)
{
	list = (st_list *)malloc(sizeof(st_list));
	if (!list) {
		fprintf(stderr, "Failed to allocate memory for st_list.\n");
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

en_mixed_return_code mixed_visual_list_add_first_elem(st_list *list, void *elem)
{
	int ret;
	st_list_item *list_item = NULL;

	if (!list || !elem) {
		fprintf(stderr, "Null parameter received.\n");
		return MIXED_RET_ERROR;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		fprintf(stderr, "Failed to allocate memory for st_list_item.\n");
		return MIXED_RET_ERROR;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = elem;

	ret = list_add_first(list, list_item);
	if (!ret) {
		fprintf(stderr, "Failed to add first element to list.\n");
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

/**************************************************************************************************/

en_mixed_return_code mixed_visual_list_add_elem(st_list *list, void *elem)
{
	int ret;
	st_list_item *list_item = NULL;

	if (!list || !elem) {
		fprintf(stderr, "Null parameter received.");
		return MIXED_RET_ERROR;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		fprintf(stderr, "Failed to allocate memory for st_list_item.");
		return MIXED_RET_ERROR;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = elem;

	ret = list_add_next(list, list_item);
	if (ret != 0) {
		fprintf(stderr, "Failed to add element to list.");
		return MIXED_RET_ERROR;
	}

	return MIXED_RET_SUCCESS;
}

