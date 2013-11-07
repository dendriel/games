/*
 * Trigger_give_damage.h
 *
 *  Created on: 07/11/2013
 *      Author: marta
 */

#ifndef TRIGGER_GIVE_DAMAGE_H_
#define TRIGGER_GIVE_DAMAGE_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_give_damage: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_give_damage(const long& damage_points, Trigger *next=NULL, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_GIVE_DAMAGE,
				repeat,
				next,
				enabled,
				damage_points)		//! Object that will be given.
	{}

	/**
	 * \brief Returns the damage points to do in the character.
	 */
	inline long get_damage(void)
	{
		return m_Gen_param_1;
	}
};

#endif /* TRIGGER_GIVE_DAMAGE_H_ */
