/*
 * Lever.cpp
 *
 *  Created on: 21/10/2013
 *      Author: vitor
 */


#include "Lever.h"
#include "sprites_data.h"

static st_rect Lever_rect_size(0,0,24,24);
#define LEVER_OBJECT_NAME "lever"

Lever::Lever(const unsigned int x_8px, const unsigned int y_8px):
GameObject(Lever_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		SPRITE_FACING_NONE,
		LEVER_OBJECT_NAME)
{}
