#include "gBrain_video_intf.h"

#include "game_defines.h"
#include "game_structs.h"

#include "mixedAPI.h"
#include "mixedAPI_defines.h"

#include "debug.h"


en_game_return_code gBrain_video_intf_test(void)
{
	st_game_msg msg;
	en_game_return_code ret;

	memset(&msg, 0, sizeof(st_game_msg));

	/* Fill the message. */
	msg.id = GAMEBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;
	/* Fill visual elements. */
	msg.v_elem.type = GVIDEO_VTYPE_SCEN_STATIC;
	msg.v_elem.h = 0;
	msg.v_elem.v = 0;
	msg.v_elem.image = load_bitmap("./media/img/800x600.bmp", NULL);

	if (!msg.v_elem.image) {
		critical("Failed to load scenery bitmap.");
		return GAME_RET_ERROR;
	}

	ret = mixed_mqueue_send_msg(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to add scenery!!!");
	}

	memset(&msg, 0, sizeof(st_game_msg));

	/* Fill the message. */
	msg.id = GAMEBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;
	/* Fill visual elements. */
	msg.v_elem.type = GVIDEO_VTYPE_ELEM_STATIC;
	msg.v_elem.h = 90;
	msg.v_elem.v = 90;
	msg.v_elem.image = load_bitmap("./media/img/espada.bmp", NULL);

	if (!msg.v_elem.image) {
		critical("Failed to load  espada bitmap.");
		return GAME_RET_ERROR;
	}

	ret = mixed_mqueue_send_msg(GVIDEO_MQUEUE_NAME, GAME_MQUEUE_PRIO_1, &msg);
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to add espada!!!");
	}

	return GAME_RET_SUCCESS;
}

