#include "gController_action_move.h"

#include "game_structs.h"

#include "gBrain_defines.h"

#include "mixedAPI.h"


/**************************************************************************************************/

void gController_action_move(en_ctrl_move direction)
{
	st_game_msg msg;
	en_mixed_return_code ret;

	memset(&msg, 0, sizeof(msg));

	msg.id = GCONTROLLER_MOD_ID;
	msg.type = GAME_ACTION_MOVE_ELEM;

	msg.control.move = direction;

	/* Send the request. */
	ret = mixed_mqueue_send(GBRAIN_MQUEUE_NAME, GAME_MQUEUE_PRIO_2, &msg);
	if (ret != MIXED_RET_SUCCESS) {
		return;
	}

	/* There is no need to receive any confirmation. */
}

