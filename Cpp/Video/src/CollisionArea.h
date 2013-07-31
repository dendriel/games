/*
 * CollisionArea.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONAREA_H_
#define COLLISIONAREA_H_

#include <vector>
#include "CollisionElement.h"

using namespace std;

#define COLL_AREA_SIZE 100	//!< Default collision area size in pixels.

class CollisionArea {
private:
	vector <CollisionElement *> m_collElements_stack;

public:
	/**
	 * \brief Add an element into the collision area stack.
	 */
	void add_element(CollisionElement& element);
};


#endif /* COLLISIONAREA_H_ */
