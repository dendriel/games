/*
 * CollisionElement.cpp
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#include "CollisionElement.h"

/*************************************************************************************************/

CollisionElement::CollisionElement(const st_rect rect, const st_rect action_rect):
m_CollRect(rect),
m_ActionCollRect(action_rect)
{}
