#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#include "mixedAPI.h"
#include "mixedAPI_defines.h"


/**************************************************************************************************/

en_mixed_return_code mixed_open_mqueue(mqd_t *mqueue, const char *mq_name, const unsigned mq_size)
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
	*mqueue = mq_open(mq_name, O_CREAT | O_RDONLY, 0644, &attr);
	if (*mqueue == (mqd_t)-1) {
		fprintf(stderr, "Failed to open mqueue. name: %s; errno: %d; msg: %s",
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
		fprintf(stderr, "Failed to close the mqueue. name: %s; errno: %d; msg: %s",
			mq_name, errno, strerror(errno));
	}

	ret = mq_unlink(mq_name);
	if (ret != 0) {
		fprintf(stderr, "Failed to unlink the mqueue. name: %s; errno: %d; msg: %s",
			mq_name, errno, strerror(errno));
	}
}

