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

	~CollisionDomain(void);

	/**
	 * \brief Fill up the collision areas.
	 * \param area_size The collision area size.
	 * \retun 0 for successful operation; -1 if something went wrong.
	 */
	void build_collAreas(const st_element_pos& area_size);

};


#endif /* COLLISIONDOMAIN_H_ */
