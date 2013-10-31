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
	//! SECOND Reaction chain.
	Trigger *activate_lever =
				new Trigger(ACTION_TOUCH,
						ACTION_CHANGE_SPRITE,
						1,
						NULL,
						false,
						this->get_Id(),
						SPRITE_POSITION_4);
	set_Trigger(activate_lever);

	//! SECOND Reaction chain.
	Trigger *change_reaction =
			new Trigger(ACTION_NONE,
						ACTION_CHANGE_REACTION,
						-1,
						activate_lever,
						false,
						this->get_Id(),
						ACTION_TOUCH);
	set_Trigger(change_reaction);

	//! FIRST Reaction chain.
	Trigger *change_sprite_reaction =
			new Trigger(ACTION_NONE,
						ACTION_CHANGE_SPRITE,
						-1,
						change_reaction,
						false,
						this->get_Id(),
						SPRITE_POSITION_3);
	set_Trigger(change_sprite_reaction);

	//!< FIRST Reaction chain.
	Trigger *remove_object_reaction =
			new Trigger(ACTION_NONE,
						ACTION_REMOVE_OBJECT,
						-1,
						change_sprite_reaction,
						false,
						object_id);
	set_Trigger(remove_object_reaction);

	//! FIRST Reaction initial trigger.
	Trigger *check_for_object =
			new Trigger(ACTION_TOUCH,
						ACTION_CHECK_OBJECT,
						-1,
						remove_object_reaction,
						true,
						object_id);
	set_Trigger(check_for_object);

}
