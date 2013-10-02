/*
 * Timming.cpp
 *
 *  Created on: 01/10/2013
 *      Author: vitor
 */

#include "Timming.h"
#include <nds.h>
#include <time.h>

//!< The speed of the timer when using ClockDivider_1024.
#define TIMER_SPEED (BUS_CLOCK/1024)


/*************************************************************************************************/

void Timming::start(void)
{
	timerStart(0, ClockDivider_1024, 0, NULL);
}

/*************************************************************************************************/

void Timming::stop(void)
{
	(void) timerPause(0);
}

/*************************************************************************************************/

void Timming::reset(void)
{
	m_Ticks = 0;
}


/*************************************************************************************************/

void Timming::update(void)
{
	m_Ticks += timerElapsed(0);
}

/*************************************************************************************************/

unsigned int Timming::elapsed_seconds(void)
{
	return m_Ticks/TIMER_SPEED;
}

/*************************************************************************************************/

unsigned int Timming::elapsed_miliseconds(void)
{
	return ((m_Ticks%TIMER_SPEED)*1000) /TIMER_SPEED;
}

/*************************************************************************************************/
