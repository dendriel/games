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
	 * \brief Get any key down.
	 */
	void get_keyDown(void);

	/*
	 * \brief Return an action from the player.
	 */
	SDLKey get_Action(void);

};


#endif /* CONTROLLER_H_ */
