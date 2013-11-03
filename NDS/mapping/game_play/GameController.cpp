/*
 * GameController.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GameController.h"

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
	scanKeys();
	int keys = keysHeld();

	//TODO: Poll touch pad first.

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
