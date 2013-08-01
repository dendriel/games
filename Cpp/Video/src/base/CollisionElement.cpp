/*
 * CollisionElement.cpp
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#include "CollisionElement.h"

/*************************************************************************************************/

CollisionElement::CollisionElement(const en_collElement_type type):
m_Type(type) {}

/*************************************************************************************************/

inline en_collElement_type CollisionElement::type(void)
{
	return m_Type;
}
