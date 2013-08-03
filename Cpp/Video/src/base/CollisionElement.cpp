/*
 * CollisionElement.cpp
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#include "CollisionElement.h"

/*************************************************************************************************/

CollisionElement::CollisionElement(const en_collElement_type type):
m_Type(type)
{
	cout << "CollisionElement created!";
	cout << " m_Type: " << m_Type << "; type: " << type << endl;
}

/*************************************************************************************************/

void CollisionElement::add_vertex(const st_collVertex& vertex)
{
	m_Vertices.push_back(vertex);
}

/*************************************************************************************************/

en_collElement_type CollisionElement::type(void)
{
	return m_Type;
}
