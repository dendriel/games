/*
 * GameController.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GameController.h"
#include <assert.h>
#include <nds.h>
#include "Gpos.h"

#include "util.h"


/**
 * \brief Translate the touched point and pressed keys (if any) into an action.
 */
static en_action translate_pad_area(const short& area, const unsigned int& keys);

/*************************************************************************************************/

en_action GameController::get_user_action(void)
{
	/*
	  KEY_A      = BIT(0),  //!< Keypad A button.		| None.
	  KEY_B      = BIT(1),  //!< Keypad B button.		| None.
	  KEY_SELECT = BIT(2),  //!< Keypad SELECT button.	| None.
	  KEY_START  = BIT(3),  //!< Keypad START button.	| Clear console (debug purpose).
	  KEY_RIGHT  = BIT(4),  //!< Keypad RIGHT button.	| Move right;
	  KEY_LEFT   = BIT(5),  //!< Keypad LEFT button.	| Move left;
	  KEY_UP     = BIT(6),  //!< Keypad UP button.		| Move up;
	  KEY_DOWN   = BIT(7),  //!< Keypad DOWN button.	| Move down;
	  KEY_R      = BIT(8),  //!< Right shoulder button.	| Action/touch.
	  KEY_L      = BIT(9),  //!< Left shoulder button.	| Action/touch
	  KEY_X      = BIT(10), //!< Keypad X button.		| None.
	  KEY_Y      = BIT(11), //!< Keypad Y button.		| None.
	  KEY_TOUCH  = BIT(12), //!< Touchscreen pendown.	| None.
	  KEY_RIGHT + KEY_L									| Run right.
	  KEY_LEFT  + KEY_L									| Run left.
	  KEY_UP    + KEY_L									| Run up.
	  KEY_DOWN  + KEY_L									| Run down.
*/
	touchPosition touch;
	unsigned int keys;

	scanKeys();
	keys = keysHeld();

	touchRead(&touch);

	//TODO: Poll touch pad first.

	//! Check touch pad. If the point is different from the default (0,0), then process.
	if ((touch.px > 0) && (touch.py > 0)) {
		const short area = Gpos::point_area_in_rect(
				static_cast<int>(touch.px), static_cast<int>(touch.py),
				static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT));

		// logical error if the point isn't from the screen area.
		assert(area >= 0);

		return translate_pad_area(area, keys);
	}

	if (keys & KEY_A) {
		return ACTION_NONE;
	}

	if (keys & KEY_B) {
		return ACTION_NONE;
	}

	if (keys & KEY_START) {
		return ACTION_CONSOLE_CLEAR;
		//return ACTION_NONE;
	}

	if (keys & KEY_SELECT) {
		return ACTION_NONE;
	}

	if (keys & KEY_UP) {
		return (keys & KEY_L)? ACTION_RUN_NORTH : ACTION_WALK_NORTH;
	}

	if (keys & KEY_DOWN) {
		return (keys & KEY_L)? ACTION_RUN_SOUTH : ACTION_WALK_SOUTH;
	}

	if (keys & KEY_LEFT) {
		return (keys & KEY_L)? ACTION_RUN_WEST : ACTION_WALK_WEST;
	}

	if (keys & KEY_RIGHT) {
		return (keys & KEY_L)? ACTION_RUN_EAST : ACTION_WALK_EAST;
	}

	if ((keys & KEY_L) || (keys & KEY_R)) {

		return ACTION_TOUCH;
	}

	return ACTION_NONE;
}

/*************************************************************************************************/

static en_action translate_pad_area(const short& area, const unsigned int& keys)
{
	switch(area) {
		case 0:
			return (keys & KEY_L)? ACTION_RUN_NORTH : ACTION_WALK_NORTH;
		case 1:
			return (keys & KEY_L)? ACTION_RUN_EAST : ACTION_WALK_EAST;
		case 2:
			return (keys & KEY_L)? ACTION_RUN_SOUTH : ACTION_WALK_SOUTH;
		case 3:
			return (keys & KEY_L)? ACTION_RUN_WEST : ACTION_WALK_WEST;
		default:
			return ACTION_NONE;
	}
	return ACTION_NONE;
}

/*************************************************************************************************/
