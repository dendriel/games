#include <stdbool.h>
#include <allegro.h>

#include "gController_keyboard_defines.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gBrain_defines.h"
#include "gSystem_defines.h"

#include "mixedAPI.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\b Extern from game controller main module.
 */
extern char Gcontroller_label[GAME_MOD_LABEL_SIZE];

/**************************************************************************************************/
/**
 *	\b Trigger movement events.
 *	\p key Reference to the event that will be processed.
 */
static void gController_keyboard_move(const int key);

/**************************************************************************************************/
/**
 *	\b Trigger miscellaneous events, as accessing menu pausing and exiting the game.
 *	\p key Reference to the event that will be processed.
 */
static void gController_keyboard_misc(const int key);

/**************************************************************************************************/
/**
 *	\b Send the key action to the brain module (not the key, but the corresponding action).
 *	\p dest_mod The module queue name that will process the action.
 *	\p action The action to be processed.
 */
static void gController_send(const char *dest_mod, const en_game_msg_type action);


/**************************************************************************************************/

void gController_keyboard_thread(void *data)
{
	int key_pressed;

	clear_keybuf();

	while((key_pressed = readkey())) {

		key_pressed = key_pressed >> 8;

		switch(key_pressed) {
			/* Movement event. */
			case KEY_UP:
			case KEY_RIGHT:
			case KEY_DOWN:
			case KEY_LEFT:
				gController_keyboard_move(key_pressed);
			break;

			case KEY_ESC:
				gController_keyboard_misc(key_pressed);
			break;

			default:
				error("No action registered to this key. Key %d", (key_pressed));
			break;
		}

		clear_keybuf();
		usleep(GCONTROLLER_KB_ACTION_INTERVAL_IN_USEC);
	}
}

/**************************************************************************************************/

static void gController_keyboard_move(const int key)
{
	switch(key) {
		case KEY_UP:
			gController_send(GBRAIN_MQUEUE_NAME, GAME_ACTION_MOVE_UP);
		break;

		case KEY_RIGHT:
			gController_send(GBRAIN_MQUEUE_NAME, GAME_ACTION_MOVE_RIGHT);
		break;

		case KEY_DOWN:
			gController_send(GBRAIN_MQUEUE_NAME, GAME_ACTION_MOVE_DOWN);
		break;

		case KEY_LEFT:
			gController_send(GBRAIN_MQUEUE_NAME, GAME_ACTION_MOVE_LEFT);
		break;

		default:
			error("Received invalid key: %d", key);
		break;
	}
}

/**************************************************************************************************/

static void gController_keyboard_misc(const int key)
{
	switch(key) {
		case KEY_ESC:
			gController_send(GSYSTEM_MQUEUE_NAME, GAME_ACTION_HALT_MODULE);
		break;

		case KEY_ENTER:
			//gController_action_misc(GCTRL_GAME_PAUSE);
		break;

		default:
			error("Received invalid key: %d", key);
		break;
	}
}

/**************************************************************************************************/


/**************************************************************************************************/

static void gController_send(const char *dest_mod, const en_game_msg_type action)
{
	st_game_msg msg;
	en_mixed_return_code ret;

	memset(&msg, 0, sizeof(msg));

	msg.id = GCONTROLLER_MOD_ID;
	msg.type = action;

	/* Send the request. */
	ret = mixed_mqueue_send(dest_mod, GAME_MQUEUE_PRIO_2, &msg);
	if (ret != MIXED_RET_SUCCESS) {
		return;
	}

	/* There is no need to receive any confirmation. */
}

