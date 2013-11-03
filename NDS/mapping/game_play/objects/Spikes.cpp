/*
 * Spikes.cpp
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */


#include "Spikes.h"
#include "triggers.h"
#include "sprites_data.h"
#include "util.h"

static st_rect Spikes_rect_size(3,8,31,31);
#define LEVER_OBJECT_NAME "Spikes"

Spikes::Spikes(const unsigned int x_8px, const unsigned int y_8px, bool display):
GameObject(Spikes_rect_size,
		(u8*)spikes_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_3,
		SPRITE_POSITION_0,
		LEVER_OBJECT_NAME,
		display)
{
	Trigger_change_sprite *change_sprite = new Trigger_change_sprite(this->get_Id(), SPRITE_POSITION_3);
	set_Trigger(change_sprite);

	Trigger_delay *delay = new Trigger_delay(100,
											change_sprite,
											ACTION_TOUCH,
											true);
	set_Trigger(delay);
}

