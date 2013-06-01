#include "gBrain_video_intf.h"

#include "game_defines.h"
#include "game_structs.h"
#include "gameVideo_structs.h"

#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"


en_game_return_code gBrain_video_intf_test()
{
	st_visual v_elem;
	en_game_return_code ret;

	memset(&v_elem, 0, sizeof(v_elem));

	/* Fill visual elements. */
	v_elem.type = GVIDEO_VTYPE_SCEN_STATIC;
	v_elem.h = 0;
	v_elem.v = 0;
	v_elem.image = load_bitmap("./media/img/800x600.bmp", NULL);

	if (!v_elem.image) {
		critical("Failed to load scenery bitmap.");
		return GAME_RET_ERROR;
	}

	ret = gBrain_video_intf_add_elem(&v_elem);
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to add scenery!!!");
	}

	memset(&v_elem, 0, sizeof(v_elem));

	/* Fill visual elements. */
	v_elem.type = GVIDEO_VTYPE_ELEM_STATIC;
	v_elem.h = 90;
	v_elem.v = 90;
	v_elem.image = load_bitmap("./media/img/espada.bmp", NULL);

	if (!v_elem.image) {
		critical("Failed to load  espada bitmap.");
		return GAME_RET_ERROR;
	}
	debug("v_elem.image %p", v_elem.image);

	ret = gBrain_video_intf_add_elem(&v_elem);
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to add espada!!!");
	}

	return GAME_RET_SUCCESS;
}

en_game_return_code gBrain_video_intf_add_elem(st_visual *v_elem)
{
	en_mixed_return_code ret;
	mqd_t gvideo_mqueue;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	ret = mixed_open_mqueue(&gvideo_mqueue,
							GAMEVIDEO_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_SEND_MODE);
	if (ret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Fill the message. */
	msg.id = GAMEBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;

	msg.v_elem.type = v_elem->type;
	msg.v_elem.h = v_elem->h;
	msg.v_elem.v = v_elem->v;
	msg.v_elem.image = v_elem->image;


	ret = mq_send(gvideo_mqueue, (void *)&msg, GAME_MQUEUE_SIZE, GAME_MQUEUE_PRIO_1);

	if (ret != 0) {
		critical("Failed to send message. errno: %d; msg: %s\n", errno, strerror(errno));
		mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
		return GAME_RET_ERROR;
	}

	mixed_close_mqueue_sender(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);

	return GAME_RET_SUCCESS;
}
