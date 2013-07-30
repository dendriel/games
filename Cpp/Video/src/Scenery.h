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
#include "VisualElement.h"

using namespace std;

// 20x15 - Testing purpose
const unsigned int layer0[] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //1
		2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3, //5
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3, //10
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3, //15
};


class Scenery {
private:
	Video& m_Video;
	vector <VisualElement *> m_UnderLayer_list;

public:
	Scenery(Video& video);
};


#endif /* SCENERY_H_ */
