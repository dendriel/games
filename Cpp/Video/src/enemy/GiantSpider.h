/*
 * GiantSpider.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef GIANTSPIDER_H_
#define GIANTSPIDER_H_

#include "Enemy.h"


#define IMAGE_VIEWPOINTS_SOURCE_PATH "image/aranha_288x320.bmp"
#define IMAGE_POSITIONS 4		//!< How much positions are in the image.
#define IMAGE_VIEWS 3			//!< How much views are in the image.


class GiantSpider: public Enemy {
private:

public:
	GiantSpider(const int x = 100, const int y = 100);
private:

};


#endif /* GIANTSPIDER_H_ */
