/*
 * Trigger_change_sprite.h
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */

#ifndef TRIGGER_CHANGE_SPRITE_H_
#define TRIGGER_CHANGE_SPRITE_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_change_sprite: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_change_sprite(const long& object_id, const long& new_sprite, Trigger *next=NULL, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_CHANGE_SPRITE,
				repeat,
				next,
				enabled,
				object_id,		//! Object to update.
				new_sprite)		//! New object sprite.
	{}

	/**
	 * \brief Returns the unique id of the object to be updated.
	 */
	inline long get_object_id(void)
	{
		return m_Gen_param_1;
	}

	inline long get_new_sprite(void)
	{
		return m_Gen_param_2;
	}
};

#endif /* TRIGGER_CHANGE_SPRITE_H_ */
