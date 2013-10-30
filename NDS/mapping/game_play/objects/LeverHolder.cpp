/*
 * LeverHolder.cpp
 *
 *  Created on: 29/10/2013
 *      Author: vitor
 */


#include "LeverHolder.h"
#include "sprites_data.h"

static st_rect LeverHolder_rect_size(4,8,24,24);
#define LEVERHOLDER_OBJECT_NAME "lever holder"

LeverHolder::LeverHolder(const unsigned int x_8px, const unsigned int y_8px, bool display):
GameObject(LeverHolder_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_2,
		SPRITE_POSITION_2,
		LEVERHOLDER_OBJECT_NAME,
		display)
{}

LeverHolder::LeverHolder(const unsigned int x_8px, const unsigned int y_8px, const long object_id, const bool display):
GameObject(LeverHolder_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_2,
		SPRITE_POSITION_2,
		LEVERHOLDER_OBJECT_NAME,
		display)
{
	// I believe that the data from these chain reactions will be lost (so far).
	//!< Reaction chain.
	en_sprite_object_positions *new_sprite_position = new en_sprite_object_positions();
	*new_sprite_position = SPRITE_POSITION_3;
	st_trigger *change_sprite_reaction = new st_trigger(ACTION_NONE,
								ACTION_CHANGE_SPRITE,
								-1,
								NULL,
								this->get_Id(),
								new_sprite_position);
	//!< Reaction chain.
	st_trigger *remove_object_reaction = new st_trigger(ACTION_NONE,
								ACTION_REMOVE_OBJECT,
								-1,
								change_sprite_reaction,
								object_id,
								NULL);

	//! Reaction initial trigger.
	st_trigger check_for_object(ACTION_TOUCH,
								ACTION_CHECK_OBJECT,
								-1,
								remove_object_reaction,
								object_id,
								NULL);
	set_Trigger(check_for_object);
}
