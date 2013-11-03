/*
 * StatusElement.h
 *
 *  Created on: 02/11/2013
 *      Author: vitor
 */

#ifndef STATUSELEMENT_H_
#define STATUSELEMENT_H_

static const unsigned short Default_HealthPoints = 6;

/**
 * \brief Class to hold any game element that have status/attributes.
 */
class StatusElement {
private:
	unsigned short m_HealthPoints;			//! Current element health points.
	unsigned short m_HealthPoints_max;		//! Max element health points.

public:
	/**
	 * \brief Class constructor.
	 */
	StatusElement(const unsigned short health_points_max=Default_HealthPoints):
		m_HealthPoints(health_points_max),
		m_HealthPoints_max(health_points_max)
	{}

	inline unsigned short get_health_points(void)
	{
		return m_HealthPoints;
	}

	/**
	 * \brief Add health points. Will not go over m_HealthPoints_max.
	 */
	inline void add_health_points(const unsigned short& points)
	{
		if ((m_HealthPoints + points) > m_HealthPoints_max) {
			m_HealthPoints = m_HealthPoints_max;
		}
		else {
			m_HealthPoints += points;
		}
	}

	/**
	 * \brief Remove health points. Can't go bellow 0.
	 */
	inline void dec_health_points(const unsigned short& points)
	{
		if ((m_HealthPoints - points) < 0) {
			m_HealthPoints = 0;
		}
		else {
			m_HealthPoints -= points;
		}
	}
};

#endif /* STATUSELEMENT_H_ */
