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

Lever::Lever(const unsigned int x_8px, const unsigned int y_8px, bool display):
GameObject(Lever_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_1,
		SPRITE_POSITION_0,
		LEVER_OBJECT_NAME,
		display)
{
	Trigger *give_item = new Trigger(ACTION_TOUCH,
						ACTION_GIVE_OBJECT,
						1,
						NULL,
						get_Id());
	set_Trigger(give_item);
}
