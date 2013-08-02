/*
 * Rock1.h
 *
 *  Created on: 01/08/2013
 *      Author: vitor
 */

#ifndef ROCK1_H_
#define ROCK1_H_

#include <iostream>
#include <string>
#include "Object.h"

#define ROCK1_IMAGE_VIEWPOINTS_SOURCE_PATH "image/rock1_39x31.bmp"
#define ROCK1_IMAGE_POSITIONS 1		//!< How much positions are in the image.
#define ROCK1_IMAGE_VIEWS 1			//!< How much views are in the image.

const st_collVertex rock1_coll_vertices[] = {
		/* Rect   -   Area ID*/
		{{0,0,39,31}, -1}
};


class Rock1: public Object {
public:
	Rock1(const int x, const int y, const string image = ROCK1_IMAGE_VIEWPOINTS_SOURCE_PATH,
			const unsigned int positions = ROCK1_IMAGE_POSITIONS,
			const unsigned int views = ROCK1_IMAGE_VIEWS);
};


#endif /* ROCK1_H_ */
