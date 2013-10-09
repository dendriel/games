/*
 * GameController.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GameController.h"

/*************************************************************************************************/

en_char_action GameController::get_user_action(void)
{
	/*
	  KEY_A      = BIT(0),  //!< Keypad A button.
	  KEY_B      = BIT(1),  //!< Keypad B button.
	  KEY_SELECT = BIT(2),  //!< Keypad SELECT button.
	  KEY_START  = BIT(3),  //!< Keypad START button.
	  KEY_RIGHT  = BIT(4),  //!< Keypad RIGHT button.
	  KEY_LEFT   = BIT(5),  //!< Keypad LEFT button.
	  KEY_UP     = BIT(6),  //!< Keypad UP button.
	  KEY_DOWN   = BIT(7),  //!< Keypad DOWN button.
	  KEY_R      = BIT(8),  //!< Right shoulder button.
	  KEY_L      = BIT(9),  //!< Left shoulder button.
	  KEY_X      = BIT(10), //!< Keypad X button.
	  KEY_Y      = BIT(11), //!< Keypad Y button.
	  KEY_TOUCH  = BIT(12), //!< Touchscreen pendown.
*/
	scanKeys();
	int keys = keysHeld();

	//TODO: Poll touch pad first.

	if(keys & KEY_A) {
		return ACTION_NONE;
	}

	if(keys & KEY_B) {
		return ACTION_NONE;
	}

	if(keys & KEY_START) {
		return ACTION_NONE;
	}

	if(keys & KEY_SELECT) {
		return ACTION_NONE;
	}

	if(keys & KEY_UP) {
		return ACTION_WALK_NORTH;
	}

	if(keys & KEY_DOWN) {
		return ACTION_WALK_SOUTH;
	}

	if(keys & KEY_LEFT) {
		return ACTION_WALK_WEST;
	}

	if(keys & KEY_RIGHT) {
		return ACTION_WALK_EAST;
	}

	return ACTION_NONE;
}

/*************************************************************************************************/
