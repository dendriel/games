/*
 * GameController.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GameController.h"


/*************************************************************************************************/

en_facing GameController::get_held_direction(void)
{
	scanKeys();

	int keys = keysHeld();

	if(keys & KEY_UP) {
		return W_UP;
	}

	if(keys & KEY_DOWN) {
		return W_DOWN;
	}

	if(keys & KEY_LEFT) {
		return W_LEFT;
	}

	if(keys & KEY_RIGHT) {
		return W_RIGHT;
	}

	return W_DEFAULT;
}

/*************************************************************************************************/
