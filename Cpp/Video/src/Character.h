/*
 * Hero.h
 *
 *  Created on: 31/07/2013
 *      Author: vitor
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include <string>

#include "VisualElement.h"
#include "CollisionElement.h"
#include "viewpoints.h"

#define CHAR_DEFAULT_SPEED_MS 200
#define CHAR_DEFAULT_WALK_LENGTH 20
#define CHAR_DEFAULT_IMAGE_SOURCE_PATH "image/aranha_288x320.bmp"
#define CHAR_DEFAULT_IMAGE_POSITIONS 4
#define CHAR_DEFAULT_IMAGE_VIEWS 3

const st_collVertex player_coll_vertices[] = {
		/* Rect   -   Area ID*/
		{{0,0,0,0}, {-1,-1,-1,-1}}
};

class Character: public VisualElement, public CollisionElement {
private:
	en_image_viewpoints m_StandPosition;
	string m_ImageSourcerPath;
	unsigned int m_ImagePositions;
	unsigned int m_ImageViews;

public:
	Character(const int x = 0, const int y = 0,
			string img_source = CHAR_DEFAULT_IMAGE_SOURCE_PATH,
			const unsigned int postions = CHAR_DEFAULT_IMAGE_POSITIONS,
			const unsigned int views = CHAR_DEFAULT_IMAGE_VIEWS);

	/* This functions are duplicated in enemy base-class. Maybe create some class for moving
	 * objects (if no differences between made up)
	 */
	void move_up();
	void move_right();
	void move_left();
	void move_down();
	void stand();
public:
	unsigned int m_Speed_ms;
};

#endif /* CHARACTER_H_ */
