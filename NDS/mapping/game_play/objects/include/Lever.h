/*
 * Lever.h
 *
 *  Created on: 21/10/2013
 *      Author: vitor
 */

#ifndef LEVER_H_
#define LEVER_H_

#include "GameObject.h"

class Lever: public GameObject {
public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 */
	Lever(const unsigned int x_8px, const unsigned int y_8px);
};

#endif /* LEVER_H_ */
