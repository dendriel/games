/*
 * CollisionDomain.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONDOMAIN_H_
#define COLLISIONDOMAIN_H_

#include <iostream>
#include <vector>
#include "CollisionArea.h"
#include "viewpoints.h"

using namespace std;

class CollisionDomain {
private:
	vector <CollisionArea> *m_collAreas;

public:
	CollisionDomain(void);
	~CollisionDomain(void);

	/**
	 * \brief Fill up the collision areas.
	 * \parameter area_size The collision area size.
	 * \return 0 for successful operation; -1 if something went wrong.
	 */
	void build_collAreas(const st_element_pos& area_size);

	/**
	 * \brief Register the elements in the corresponding collision areas.
	 * \parameter element The element to be added.
	 */
	void add_collisionElement(CollisionElement *element);

};


#endif /* COLLISIONDOMAIN_H_ */
