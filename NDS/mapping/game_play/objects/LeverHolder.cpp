/*
 * LeverHolder.cpp
 *
 *  Created on: 29/10/2013
 *      Author: vitor
 */


#include "LeverHolder.h"
#include "triggers.h"
#include "sprites_data.h"

static st_rect LeverHolder_rect_size(4,8,24,23);
#define LEVERHOLDER_OBJECT_NAME "lever holder"

LeverHolder::LeverHolder(const unsigned int x_8px, const unsigned int y_8px, const bool display):
GameObject(LeverHolder_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_2,
		SPRITE_POSITION_2,
		LEVERHOLDER_OBJECT_NAME,
		display,
		true)	// blockable
{}

LeverHolder::LeverHolder(const unsigned int x_8px, const unsigned int y_8px, const long object_id, Trigger *reaction, const bool display):
GameObject(LeverHolder_rect_size,
		(u8*)lever_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_2,
		SPRITE_POSITION_2,
		LEVERHOLDER_OBJECT_NAME,
		display,
		true)
{
	//! SECOND Reaction chain.
	Trigger_change_reaction *deactivate_lever_holder =
			new Trigger_change_reaction(this->get_Id(),
											ACTION_TOUCH,
											NULL,
											reaction);

	//! SECOND Reaction chain.
	Trigger_change_sprite *activate_lever =
			new Trigger_change_sprite(this->get_Id(),
									SPRITE_POSITION_4,
									deactivate_lever_holder,
									ACTION_TOUCH);
	set_Trigger(activate_lever);

	//! SECOND Reaction chain.
	Trigger_change_reaction *change_reaction = new Trigger_change_reaction(this->get_Id(),
										ACTION_TOUCH,
										activate_lever);
	set_Trigger(change_reaction);

	//! FIRST Reaction chain.
	Trigger_change_sprite *change_sprite = new Trigger_change_sprite(this->get_Id(),
									SPRITE_POSITION_3,
									change_reaction);
	set_Trigger(change_sprite);

	//!< FIRST Reaction chain.
	Trigger_remove_object *remove_object = new Trigger_remove_object(object_id, change_sprite);
	set_Trigger(remove_object);

	//! FIRST Reaction initial trigger.
	Trigger_check_object *check_object = new Trigger_check_object(object_id,
									remove_object,
									ACTION_TOUCH,
									true);
	set_Trigger(check_object);

}
