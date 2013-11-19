/*
 * WaterTile.cpp
 *
 *  Created on: 19/11/2013
 *      Author: marta
 */


#include "WaterTile.h"
#include "triggers.h"
#include "sprites_data.h"

static st_rect WaterTile_rect_size(1,0,22,23);
#define WATERTILE_OBJECT_NAME "water tile"

WaterTile::WaterTile(const unsigned int x_8px, const unsigned int y_8px, bool display):
GameObject(WaterTile_rect_size,
		(u8*)water_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_4,
		SPRITE_POSITION_0,
		WATERTILE_OBJECT_NAME,
		display,
		true) // blockable.
{
	// Just exist and try to be a pretty tile =]
}
