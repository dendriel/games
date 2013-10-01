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

	/**
	 * \brief Start the thread to read user actions.
	 */
	void start_polling(void);
private:
	/**
	 * \brief Loop function to read user actions.
	 */
	int poll_user_actions(void);
};


#endif /* GAMECONTROLLER_H_ */
