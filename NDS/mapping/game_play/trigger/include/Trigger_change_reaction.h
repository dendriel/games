/*
 * Trigger_change_reaction.h
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */

#ifndef TRIGGER_CHANGE_REACTION_H_
#define TRIGGER_CHANGE_REACTION_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_change_reaction: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_change_reaction(const long& object_id, const long& reaction, Trigger *new_reaction, Trigger *next=NULL, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_CHANGE_REACTION,
				repeat,
				next,
				enabled,
				object_id,		//!< Object to update.
				reaction,		//!< Reaction type to be disabled.
				new_reaction)	//!< Reaction to take place.
	{}

	/**
	 * \brief Returns the unique id of the object to be updated.
	 */
	inline long get_object_id(void)
	{
		return m_Gen_param_1;
	}

	/**
	 * \brief Return the reaction to be disabled.
	 */
	inline en_action get_reaction(void)
	{
		return static_cast<en_action>(m_Gen_param_2);
	}

	inline Trigger *get_new_reaction(void)
	{
		return static_cast<Trigger *>(m_Gen_param_3);
	}
};

#endif /* TRIGGER_CHANGE_REACTION_H_ */
