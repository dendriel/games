/*
 * LeverHolder.cpp
 *
 *  Created on: 29/10/2013
 *      Author: vitor
 */


#include "LeverHolder.h"
#include "sprites_data.h"

#include <iostream>

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
	Trigger *change_sprite_reaction = new Trigger(ACTION_NONE,
								ACTION_CHANGE_SPRITE,
								-1,
								NULL,
								this->get_Id(),
								SPRITE_POSITION_3);
	set_Trigger(change_sprite_reaction);


	//std::cout << "react: " << (*get_Trigger_last()).reaction << std::endl;


	//!< Reaction chain.
	Trigger *remove_object_reaction = new Trigger(ACTION_NONE,
								ACTION_REMOVE_OBJECT,
								-1,
								get_Trigger_last(),
								object_id);
	set_Trigger(remove_object_reaction);

	//! Reaction initial trigger.
	Trigger *check_for_object = new Trigger(ACTION_TOUCH,
								ACTION_CHECK_OBJECT,
								-1,
								get_Trigger_last(),
								object_id);
	set_Trigger(check_for_object);

}
