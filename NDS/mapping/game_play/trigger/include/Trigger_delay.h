/*
 * Trigger_delay.h
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */

#ifndef TRIGGER_DELAY_H_
#define TRIGGER_DELAY_H_

#include "Trigger.h"
#include "game_actions.h"

class Trigger_delay: public Trigger {

public:
	/**
	 * \brief Class constructor.
	 */
	Trigger_delay(const long& time_cycles, Trigger *next, en_action action=ACTION_NONE, bool enabled=false, int repeat=-1):
		Trigger(action,
				ACTION_DELAY,
				repeat,
				next,
				enabled,
				time_cycles,	//! Delay time (constante).
				time_cycles)	//! Auxiliary counter.
	{}

	/**
	 * \brief Get the total cycles to wait.
	 */
	inline long get_TotalDelay(void)
	{
		return m_Gen_param_1;
	}

	/**
	 * \brief Get the current cycle..
	 */
	inline long get_RemmaingDelay(void)
	{
		return m_Gen_param_2;
	}

	/**
	 * \brief Decrement the cycle counter.
	 */
	inline void dec_RemmainingDelay(void)
	{
		if (m_Gen_param_2 > 0) {
			m_Gen_param_2--;
		}
	}

	/**
	 * \brief Restart the delay counter for future iterations.
	 */
	inline void restart_DelayCounter(void)
	{
		m_Gen_param_2 = m_Gen_param_1;
	}
};

#endif /* TRIGGER_DELAY_H_ */
