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
	Trigger_give_damage *give_damage = new Trigger_give_damage(1, NULL, ACTION_COLLISION);
	set_Trigger(give_damage);

	// Enable give damage on collision trigger.
	Trigger_change_reaction *change_reaction =
			new Trigger_change_reaction(this->get_Id(),
					ACTION_COLLISION,
					give_damage);

	set_Trigger(change_reaction);

	Trigger_change_sprite *change_sprite3 = new Trigger_change_sprite(this->get_Id(), SPRITE_POSITION_3, change_reaction);
	set_Trigger(change_sprite3);

	Trigger_delay *delay2 = new Trigger_delay(3, change_sprite3);
	set_Trigger(delay2);

	Trigger_change_sprite *change_sprite2 = new Trigger_change_sprite(this->get_Id(), SPRITE_POSITION_2, delay2);
	set_Trigger(change_sprite2);

	Trigger_delay *delay1 = new Trigger_delay(4, change_sprite2);
	set_Trigger(delay1);

	Trigger_change_sprite *change_sprite1 = new Trigger_change_sprite(this->get_Id(), SPRITE_POSITION_1, delay1);
	set_Trigger(change_sprite1);

	Trigger_delay *delay = new Trigger_delay(50,
											change_sprite1,
											ACTION_COLLISION,
											true,
											1);
	set_Trigger(delay);
}

