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
#include "Controller.h"
#include "Character.h"
#include "CollisionDomain.h"
#include "VisualElement.h"

using namespace std;

class Scenery {
private:
	Controller m_Control;
	CollisionDomain m_CollDomain_dynamic;
	CollisionDomain m_CollDomain_static;
	Video& m_Video;
	vector <VisualElement *> m_UnderLayer_list;

public:
	Scenery(Video& video);
	~Scenery(void);

	/**
	 * \brief Add an element inside the scenery. Register the element in the Video and
	 * CollisionDomain objects.
	 * \parameter element An object that inherits the SceneryElement base-class.
	 */
	void add_element(void *element);

	/**
	 * \brief Run the scenery main line.
	 */
	void play(void);
};


#endif /* SCENERY_H_ */
