/*
 * WaterTile.h
 *
 *  Created on: 19/11/2013
 *      Author: marta
 */

#ifndef WATERTILE_H_
#define WATERTILE_H_

#include "GameObject.h"

class WaterTile: public GameObject {
public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 */
	WaterTile(const unsigned int x_8px, const unsigned int y_8px, bool display=true);
};


#endif /* WATERTILE_H_ */
