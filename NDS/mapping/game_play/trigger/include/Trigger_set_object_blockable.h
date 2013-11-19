/*
 * Trigger_set_object_blockable.h
 *
 *  Created on: 19/11/2013
 *      Author: marta
 */

#ifndef TRIGGER_SET_OBJECT_BLOCKABLE_H_
#define TRIGGER_SET_OBJECT_BLOCKABLE_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_set_object_blockable: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_set_object_blockable(const long& object_id, bool blockable, Trigger *next=NULL, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_SET_OBJECT_BLOCKABLE,
				repeat,
				next,
				enabled,
				object_id,
				blockable)
	{}
	/**
	 * \brief Returns the unique id of the object to be updated.
	 */
	inline long get_object_id(void)
	{
		return m_Gen_param_1;
	}

	inline long get_blockable(void)
	{
		return m_Gen_param_2;
	}
};



#endif /* TRIGGER_SET_OBJECT_BLOCKABLE_H_ */
