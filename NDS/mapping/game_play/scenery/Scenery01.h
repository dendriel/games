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

		// Testing purpose!!
		m_CharStartPoint_32px.x = 33;
		m_CharStartPoint_32px.y = 7;
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
		/* Testing objects. */
		m_ObjectsList 	<< new Torch(TILE_32PX_TO_8PX(61), TILE_32PX_TO_8PX(60)) << new Torch(TILE_32PX_TO_8PX(61), TILE_32PX_TO_8PX(61))
						<< new Lever(TILE_32PX_TO_8PX(63), TILE_32PX_TO_8PX(61))
		<< new Lever(TILE_32PX_TO_8PX(63), TILE_32PX_TO_8PX(62))
		<< new Torch(TILE_32PX_TO_8PX(59), TILE_32PX_TO_8PX(60))
		<< new Torch(TILE_32PX_TO_8PX(60), TILE_32PX_TO_8PX(59))
		<< new Torch(TILE_32PX_TO_8PX(60), TILE_32PX_TO_8PX(57))
		<< new Torch(TILE_32PX_TO_8PX(60), TILE_32PX_TO_8PX(56));

		GameObject *lever2 = new Lever(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(10));//new Lever(TILE_32PX_TO_8PX(16), TILE_32PX_TO_8PX(22));
		LeverHolder *lever_holder2 = new LeverHolder(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(5), lever2->get_Id());

		/* Objects from the scenery. */
		GameObject *lever = new Lever(TILE_32PX_TO_8PX(34), TILE_32PX_TO_8PX(7));//new Lever(TILE_32PX_TO_8PX(16), TILE_32PX_TO_8PX(22));
		LeverHolder *lever_holder = new LeverHolder(TILE_32PX_TO_8PX(33), TILE_32PX_TO_8PX(12), lever->get_Id());

		m_ObjectsList << lever << lever_holder << lever_holder2 << lever2;
	}
};


#endif /* SCENERY01_H_ */
