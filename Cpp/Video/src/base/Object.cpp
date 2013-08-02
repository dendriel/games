/*
 * Object.cpp
 *
 *  Created on: 01/08/2013
 *      Author: vitor
 */

#include "Object.h"

/*************************************************************************************************/
Object::Object(const int x, const int y, const string img_source, const unsigned int positions,
		const unsigned int views, const en_collElement_type type):
VisualElement(x, y),
CollisionElement(type)
{
	m_Position.x = x;
	m_Position.y = y;
	if (build_viewpoints(img_source.c_str(), positions, views, &m_Viewpoints[0]) < 0) {
		cout << "Failed to build Enemy viewpoints." << endl;
		/* Free any allocated position and Build here with default parameters. */
	}
	cout << "Object created!" << endl;
}
