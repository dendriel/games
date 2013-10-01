/*
 * GameController.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GameController.h"
#include <assert.h>
#include "timming.h"

/*************************************************************************************************/
//TODO: Doesn't work right now
void GameController::start_polling(void)
{
	/*assert(pthread_create(&m_Tid,
			NULL,
			(void *)this->poll_user_actions_wrapper(),
			NULL) == 0);
			*/
}

/*************************************************************************************************/

//TODO: Doesn't work right now
int GameController::poll_user_actions(void)
{
	while(true) {
		//TODO: the user interaction must be inside a thread.
		en_facing action = this->get_held_direction();

		switch (action) {

		case W_UP:
			break;

		case W_DOWN:
			break;

		case W_LEFT:
			break;

		case W_RIGHT:
			break;

		default:
			break;
		}

		GSLEEP(3);
	}

	return 0;
}

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
