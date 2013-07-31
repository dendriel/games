/*
 * Scenery.h
 *
 *  Created on: 29/07/2013
 *      Author: vitor
 */

#ifndef SCENERY_H_
#define SCENERY_H_

#include <iostream>
#include <vector>

#include "Video.h"
#include "CollisionDomain.h"
#include "VisualElement.h"

using namespace std;

class Scenery {
private:
	CollisionDomain m_CollDomain;
	Video& m_Video;
	vector <VisualElement *> m_UnderLayer_list;

public:
	Scenery(Video& video);

	~Scenery(void);
};


#endif /* SCENERY_H_ */
