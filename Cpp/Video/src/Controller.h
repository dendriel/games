/*
 * Controller.h
 *
 *  Created on: 20/07/2013
 *      Author: vitor
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>
#include "SDL/SDL.h"

using namespace std;

typedef enum {
	CTRL_MOVE_UP = 100,		//!< Player is moving up.
	CTRL_MOVE_RIGHT,		//!< Player is moving to the right.
	CTRL_MOVE_LEFT,			//!< Player is moving to the left.
	CTRL_MOVE_DOWN,			//!< Player is moving down.
	CTRL_KEEP_MOVING,		//!< Player keep moving to the previous direction.
	CTRL_STOP_MOVING,		//!< Player isn't moving anymore.
	CTRL_SUMMON,			//!< Summon a thing (temporary).
	CTRL_EXIT,				//!< Exit the game.
	CTRL_NONE				//!< Nothing to do.
} en_ctrl_actions;


/*
 * \brief Interact with the player.
 */
class Controller {

public:
	/*
	 * \brief Initialize controller.
	 */
	Controller(void);

	/*
	 * \brief Free controller resources.
	 */
	~Controller(void) {cout << "Controller destroyed." << endl;}

	/*
	 * \brief Get key down.
	 */
	SDLKey get_keyDown(void);

	/*
	 * \brief Return an action from the player.
	 */
	en_ctrl_actions get_action(void);

};


#endif /* CONTROLLER_H_ */
