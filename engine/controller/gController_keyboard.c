#include <stdbool.h>
#include <allegro.h>

#include "gController_keyboard_defines.h"

#include "game_defines.h"

#include "gController_action_move.h"
#include "gController_action_move_defines.h"
#include "gController_action_misc.h"
#include "gController_action_misc_defines.h"
#include "gBrain_defines.h"

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
			gController_action_move(GCTRL_MOVE_UP);
		break;

		case KEY_RIGHT:
			gController_action_move(GCTRL_MOVE_RIGHT);
		break;

		case KEY_DOWN:
			gController_action_move(GCTRL_MOVE_DOWN);
		break;

		case KEY_LEFT:
			gController_action_move(GCTRL_MOVE_LEFT);
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
			gController_action_misc(GCTRL_MISC_EXIT);
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

