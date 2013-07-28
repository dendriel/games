/*
 * GiantSpider.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "GiantSpider.h"
#include "viewpoints.h"

	GiantSpider::GiantSpider(const int x, const int y):
	Enemy(x, y, IMAGE_VIEWPOINTS_SOURCE_PATH, IMAGE_POSITIONS, IMAGE_VIEWS)
	{
		cout << "Giant Spider created!" << endl;
	}
