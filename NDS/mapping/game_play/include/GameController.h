/*
 * GameController.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "game_actions.h"

/**
 * \brief Get player actions.
 */
class GameController {
public:
	/**
	 * \brief Read and parser user actions.
	 */
	en_action get_user_action(void);

};


#endif /* GAMECONTROLLER_H_ */
