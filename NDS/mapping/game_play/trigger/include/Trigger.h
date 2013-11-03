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
	bool m_Enabled;		//!< If this trigger is enabled by default.
	long m_Id;			//!< Trigger unique identifier. Automatically generated.
protected:
	//! Some basic elements that the action may use.
	long m_Gen_param_1;		//!< Generic parameter.
	long m_Gen_param_2;		//!< Generic parameter.
	void *m_Gen_param_3;	//!< Generic parameter.

	static long s_Trigger_ids;				//!< IDs for distribute to triggers.
public:

	Trigger():
		m_Action(ACTION_NONE),
		m_Reaction(ACTION_NONE),
		m_Charges(-1),
		m_Next(NULL),
		m_Enabled(false),
		m_Id(Trigger::generate_Id()),
		m_Gen_param_1(0),
		m_Gen_param_2(0),
		m_Gen_param_3(NULL){}

	Trigger(en_action action, en_action reaction, int charges, Trigger *next=NULL, bool enabled=false, const long param_1=0, long param_2=0, void *param_3=NULL):
		m_Action(action),
		m_Reaction(reaction),
		m_Charges(charges),
		m_Next(next),
		m_Enabled(enabled),
		m_Id(Trigger::generate_Id()),
		m_Gen_param_1(param_1),
		m_Gen_param_2(param_2),
		m_Gen_param_3(param_3){}

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

	inline long get_Id(void)
	{
		return m_Id;
	}

	inline bool get_Enabled(void)
	{
		return m_Enabled;
	}

	/**
	 * \brief Disable the trigger. Set the enabled parameter to false so the trigger will not be
	 * verified anymore.
	 */
	inline void disable(void)
	{
		m_Enabled = false;
	}

	/**
	 * \brief Enable the trigger. Set the enabled parameter to false so the trigger will be verified.
	 */
	inline void enable(void)
	{
		m_Enabled = true;
	}

private:
/*************************************************************************************************/
/* Static Functions                                                                              */
/*************************************************************************************************/
	/**
	 * \brief Generate an ID for each item.
	 */
	static long generate_Id(void)
	{
		return s_Trigger_ids++;
	}
};

#endif /* TRIGGER_H_ */
