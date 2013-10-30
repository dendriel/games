/*
 * Trigger.h
 *
 *  Created on: 30/10/2013
 *      Author: vitor
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "game_actions.h"

/**
 *  Define a structure to be used as an action that triggers another action.
 */
class Trigger {
private:
	en_action m_Action;	//!< What action is the trigger.
	en_action m_Reaction;	//!< The re-action.
	int m_Charges;		//!< How much times can repeat the trigger. (-1 will be infinite times)
	Trigger *m_Next;	//!< Use to make reaction chains.
	// Some basic elements that the action may use.
	long m_Gen_id;	// Generic id for actions use (the id of given object, for example).
	int m_Gen_pos;	// Generic position for something.
public:

	Trigger():
		m_Action(ACTION_NONE),
		m_Reaction(ACTION_NONE),
		m_Charges(0),
		m_Next(NULL),
		m_Gen_id(0),
		m_Gen_pos(0){}

	Trigger(en_action action, en_action reaction, int charges, Trigger *next=NULL, long id=0, int pos=0):
		m_Action(action),
		m_Reaction(reaction),
		m_Charges(charges),
		m_Next(next),
		m_Gen_id(id),
		m_Gen_pos(pos){}

	inline en_action get_Action(void)
	{
		return m_Action;
	}

	inline en_action get_Reaction(void)
	{
		return m_Reaction;
	}

	inline int get_Charges(void)
	{
		return m_Charges;
	}

	inline void decrement_Charges(void)
	{
		if (m_Charges > 0) {
			m_Charges--;
		}
	}

	inline Trigger *get_Next_reaction(void)
	{
		return m_Next;
	}

	inline long get_Gen_id(void)
	{
		return m_Gen_id;
	}

	inline long get_Gen_pos(void)
	{
		return m_Gen_pos;
	}
};

#endif /* TRIGGER_H_ */
