/*
 * GiantSpider.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef GIANTSPIDER_H_
#define GIANTSPIDER_H_

#include <iostream>
#include "Enemy.h"

using namespace std;

#define GS_IMAGE_VIEWPOINTS_SOURCE_PATH "image/aranha_288x320.bmp"
#define GS_IMAGE_POSITIONS 4		//!< How much positions are in the image.
#define GS_IMAGE_VIEWS 3			//!< How much views are in the image.

class GiantSpider: public Enemy {
private:
	static unsigned int s_Amount;

public:

	GiantSpider(const int x = 100, const int y = 100);
	~GiantSpider(void);

	/**
	 * \brief Return the amount of this type of objects.
	 */
	static unsigned int get_amount(void)
	{
		return s_Amount;
	}
};


#endif /* GIANTSPIDER_H_ */
