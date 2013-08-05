/*
 * CollisionDomain.cpp
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#include "CollisionDomain.h"
#include "CollisionArea.h"

#include "utils.h"

#define FIND_COLLISION_AREAS(_size)\
	((_size % COLL_AREA_SIZE) || (_size == 0))? ((_size/COLL_AREA_SIZE) +1) : (_size/COLL_AREA_SIZE)

/*************************************************************************************************/

CollisionDomain::CollisionDomain(void):
m_collAreas(NULL)
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
	size_t total_coll_areas;

	m_collAreas_bounds.x = FIND_COLLISION_AREAS(bounds.x);
	m_collAreas_bounds.y = FIND_COLLISION_AREAS(bounds.y);
	total_coll_areas = m_collAreas_bounds.x * m_collAreas_bounds.y;

	m_collAreas = new vector<CollisionArea>(total_coll_areas);
}

/*************************************************************************************************/

void CollisionDomain::add_collisionElement(CollisionElement& element)
{
	/* Do for all vertices. */
	for (vector<st_collVertex>::iterator iter = element.m_Vertices.begin();
			iter != element.m_Vertices.end(); ++iter) {
		find_vertex_area_position(*iter, &element);
	}
}

/*************************************************************************************************/
/* Private Functions																			 */
/*************************************************************************************************/
/* x,y    x1,y
 *  +-----+
 *  |     |
 *  |     |
 *  +-----+
 * x,y1   x1,y1
 *
 */
void CollisionDomain::find_vertex_area_position(st_collVertex& vertex, CollisionElement *element)
{
	unsigned int x_pos = vertex.point.x;
	unsigned int y_pos = vertex.point.y;
	unsigned int x1_pos = x_pos + vertex.point.h;
	unsigned int y1_pos =  y_pos + vertex.point.w;
	double area_id;

	/* x,y - 0 */
	area_id = find_index(FIND_COLLISION_AREAS(x_pos), FIND_COLLISION_AREAS(y_pos), m_collAreas_bounds.y);
	vertex.area_id[VERTEX_POINT_UPLEFT] = area_id;
	m_collAreas->at(area_id).add_element(element);

	/* x1,y - 0 */
	area_id = find_index(FIND_COLLISION_AREAS(x1_pos), FIND_COLLISION_AREAS(y_pos), m_collAreas_bounds.y);
	vertex.area_id[VERTEX_POINT_UPRIGHT] = area_id;
	m_collAreas->at(area_id).add_element(element);

	/* x,y1 - 0 */
	area_id = find_index(FIND_COLLISION_AREAS(x_pos), FIND_COLLISION_AREAS(y1_pos), m_collAreas_bounds.y);
	vertex.area_id[VERTEX_POINT_DOWNLEFT] = area_id;
	m_collAreas->at(area_id).add_element(element);

	/* x1,y1 - 0 */
	area_id = find_index(FIND_COLLISION_AREAS(x1_pos), FIND_COLLISION_AREAS(y1_pos), m_collAreas_bounds.y);
	vertex.area_id[VERTEX_POINT_DOWNRIGHT] = area_id;
	m_collAreas->at(area_id).add_element(element);
}
