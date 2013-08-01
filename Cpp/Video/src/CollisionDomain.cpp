/*
 * CollisionDomain.cpp
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#include "CollisionDomain.h"
#include "CollisionArea.h"

#define FIND_COLLISION_AREAS(_size)\
	(_size % COLL_AREA_SIZE)? ((_size/COLL_AREA_SIZE) +1) : (_size/COLL_AREA_SIZE)

/*************************************************************************************************/

CollisionDomain::CollisionDomain(void)
{
	cout << "CollisionDomain created." << endl;
}

/*************************************************************************************************/

CollisionDomain::~CollisionDomain(void)
{
	if (m_collAreas != NULL) {
		delete m_collAreas;
	}

	cout << "Collision Domain destroyed." << endl;
}
/*************************************************************************************************/

void CollisionDomain::build_collAreas(const st_element_pos& bounds)
{
	const size_t total_coll_areas = ((FIND_COLLISION_AREAS(bounds.x)) * (FIND_COLLISION_AREAS(bounds.y)));
	m_collAreas = new vector<CollisionArea>(total_coll_areas);
}

/*************************************************************************************************/

void CollisionDomain::add_collisionElement(CollisionElement *element)
{
	/* retrieve the element bounds x,w; y,w; x,h; y,h
	 * Find the area and insert the element into it for each point
	 * Add a reference inside the collision element informing what area
	 * his bound is in it,
	 *  - There is no problem of adding an element over another.
	 */
}

/*************************************************************************************************/
