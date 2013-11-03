/*
 * Spikes.h
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */

#ifndef SPIKES_H_
#define SPIKES_H_

#include "GameObject.h"

class Spikes: public GameObject {
public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 */
	Spikes(const unsigned int x_8px, const unsigned int y_8px, bool display=true);
};


#endif /* SPIKES_H_ */
