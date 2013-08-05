/*
 * CollisionArea.cpp
 *
 *  Created on: 05/08/2013
 *      Author: vitor
 */

#include "CollisionArea.h"

void CollisionArea::add_element(CollisionElement *element)
{
	m_collElements_stack.push_back(element);
}
