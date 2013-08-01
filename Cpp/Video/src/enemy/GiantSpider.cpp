/*
 * GiantSpider.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "GiantSpider.h"
#include "viewpoints.h"


unsigned int GiantSpider::s_Amount = 0;

/*************************************************************************************************/
	GiantSpider::GiantSpider(const int x, const int y):
	Enemy(x, y, GS_IMAGE_VIEWPOINTS_SOURCE_PATH, GS_IMAGE_POSITIONS, GS_IMAGE_VIEWS)
	{
		s_Amount++;
		cout << "Giant Spider created! Total: " << s_Amount << endl;
	}

/*************************************************************************************************/
	GiantSpider::~GiantSpider(void)
	{
		s_Amount--;
		cout << "Giant Spider destroyed! Remaining: " << s_Amount << endl;
	}


/*************************************************************************************************/

