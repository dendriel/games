/*
 * Torch.h
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#ifndef TORCH_H_
#define TORCH_H_

#include "GameObject.h"

class Torch: public GameObject {
public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 * \parameter display If the object is created being displayed in the screen.
	 */
	Torch(const unsigned int x_8px, const unsigned int y_8px, bool display=true);
};

#endif /* TORCH_H_ */
