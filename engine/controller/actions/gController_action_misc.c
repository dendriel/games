#include "gController_action_misc.h"
#include "gController_action_misc_defines.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gSystem_defines.h"
#include "gBrain_defines.h"

#include "mixedAPI.h"


/**************************************************************************************************/
/**
 *	\b Send halt solicitation to System module.
 */
static void gController_action_misc_exit(void);

/**************************************************************************************************/

void gController_action_misc(en_gctrl_misc action)
{
	switch (action) {
		case GCTRL_MISC_EXIT:
			gController_action_misc_exit();
		break;

		default:
		break;
	}
}

/**************************************************************************************************/

static void gController_action_misc_exit(void)
{
	st_game_msg msg;
	en_mixed_return_code ret;

	memset(&msg, 0, sizeof(msg));

	msg.id = GCONTROLLER_MOD_ID;
	msg.type = GAME_ACTION_HALT_MODULE;

	/* Send the request. */
	ret = mixed_mqueue_send(GSYSTEM_MQUEUE_NAME, GAME_MQUEUE_PRIO_2, &msg);
	if (ret != MIXED_RET_SUCCESS) {
		return;
	}

	/* There is no need to receive any confirmation. */
}

