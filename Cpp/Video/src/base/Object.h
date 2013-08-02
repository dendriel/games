/*
 * Object.h
 *
 *  Created on: 01/08/2013
 *      Author: vitor
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <string>

#include "VisualElement.h"
#include "CollisionElement.h"

#include "viewpoints.h"

#define OBJECT_DEFAULT_X 0
#define OBJECT_DEFAULT_Y 0
#define OBJECT_DEFAULT_IMAGE_SOURCE "image/rock1_39x31.bmp"
#define OBJECT_DEFAULT_IMAGE_POSITIONS 1		//!< How much positions are in the image.
#define OBJECT_DEFAULT_IMAGE_VIEWS 1			//!< How much views are in the image.


class Object: public VisualElement, public CollisionElement {
private:
	st_element_pos m_Position;

public:
	Object(const int x = OBJECT_DEFAULT_X,
			const int y = OBJECT_DEFAULT_Y,
			const string img_source = OBJECT_DEFAULT_IMAGE_SOURCE,
			const unsigned int positions = OBJECT_DEFAULT_IMAGE_POSITIONS,
			const unsigned int views = OBJECT_DEFAULT_IMAGE_VIEWS,
			const en_collElement_type type = INANIMATED);
};

#endif /* OBJECT_H_ */
