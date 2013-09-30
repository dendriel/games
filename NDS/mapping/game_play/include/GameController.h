/*
 * GameController.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <nds.h>
#include "util.h"

/**
 * \brief Get player actions.
 */
class GameController {
public:
	/**
	 * \brief Return if directional is held.
	 * \return The held direction.
	 */
	en_facing get_held_direction(void);
};


#endif /* GAMECONTROLLER_H_ */
