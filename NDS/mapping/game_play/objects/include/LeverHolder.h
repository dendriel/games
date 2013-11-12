/*
 * LeverHolder.h
 *
 *  Created on: 29/10/2013
 *      Author: vitor
 */

#ifndef LEVERHOLDER_H_
#define LEVERHOLDER_H_

#include "GameObject.h"

class LeverHolder: public GameObject {
public:

	/**
	 * \brief Class constructor.
	 * \parameter x_8px Initial horizontal relative position.
	 * \parameter y_8px Initial vertical relative position.
	 * \parameter display If the object will be displayed in the map at first.
	 * \parameter object_id What is the needed object to trigger an reaction in this object.
	 * \parameter reaction A reaction that will be triggered after the lever is put in the lever holder and be pressed.
	 * \parameter display Display the object in the map.
	 */
	LeverHolder(const unsigned int x_8px, const unsigned int y_8px, const bool display=true);

	LeverHolder(const unsigned int x_8px, const unsigned int y_8px, const long object_id, Trigger *reaction=NULL, const bool display=true);

};

#endif /* LEVERHOLDER_H_ */
