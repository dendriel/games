/*
 * Trigger_remove_object.h
 *
 *  Created on: 03/11/2013
 *      Author: vitor
 */

#ifndef TRIGGER_REMOVE_OBJECT_H_
#define TRIGGER_REMOVE_OBJECT_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_remove_object: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_remove_object(const long& object_id, Trigger *next=NULL, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_REMOVE_OBJECT,
				repeat,
				next,
				enabled,
				object_id)		//! Object that will be given.
	{}

	/**
	 * \brief Returns the unique id of the object to be updated.
	 */
	inline long get_object_id(void)
	{
		return m_Gen_param_1;
	}
};

#endif /* TRIGGER_REMOVE_OBJECT_H_ */
