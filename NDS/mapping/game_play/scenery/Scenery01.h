/*
 * Scenery01.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef SCENERY01_H_
#define SCENERY01_H_

#include <vector>
#include "GameScenery.h"
#include "Maze3.h"
#include "Maze2.h"
#include "Sewer_mp.h"
#include "objects.h"
#include "triggers.h"

#include "util.h"

class Scenery01: public GameScenery {

public:
	/**
	 * \brief Class constructor.
	 */
	Scenery01(void)
	{
		m_Map = new Sewer_mp;
		m_CharStartPoint_32px.x = 62;
		m_CharStartPoint_32px.y = 62;

		// Testing purpose!! bridge place
		m_CharStartPoint_32px.x = 19;
		m_CharStartPoint_32px.y = 19;

		// Testing purpose!! lever holder place
		m_CharStartPoint_32px.x = 35;
		m_CharStartPoint_32px.y = 8;
	}

	/**
	 * \brief Class destructor.
	 */
	~Scenery01(void)
	{
		delete(m_Map);
		for (std::vector<GameObject *>::iterator iter = m_ObjectsList.begin(); iter != m_ObjectsList.end(); ++iter) {
			delete *iter;
		}
	}

	void fill_objects_list(void)
	{
		/* Objects from the scenery. */

		// Lever and lever holder.
		Trigger_give_damage *put_bridge = new Trigger_give_damage(2);
		GameObject *lever = new Lever(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(7));//new Lever(TILE_32PX_TO_8PX(16), TILE_32PX_TO_8PX(22));
		LeverHolder *lever_holder = new LeverHolder(TILE_32PX_TO_8PX(33), TILE_32PX_TO_8PX(12), lever->get_Id(), put_bridge);

		m_ObjectsList << lever << lever_holder;

		m_ObjectsList << new Spikes(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(10))
						<< new Spikes(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(11))
						<< new Spikes(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(12));
	}
};


#endif /* SCENERY01_H_ */
