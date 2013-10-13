/*
 * Torch.h
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#ifndef TORCH_H_
#define TORCH_H_

#include "GameObject.h"
#include "torch_data.h"

class Torch: GameObject {

public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 */
	Torch(const unsigned int x_8px, const unsigned int y_8px);

};

#endif /* TORCH_H_ */
