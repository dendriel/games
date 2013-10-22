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
		//m_CharStartPoint_32px.x = 14;
		//m_CharStartPoint_32px.y = 20;
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
		m_ObjectsList.push_back(new Torch(TILE_32PX_TO_8PX(60), TILE_32PX_TO_8PX(60)));
		m_ObjectsList.push_back(new Lever(TILE_32PX_TO_8PX(63), TILE_32PX_TO_8PX(60)));

		/* Objects from the scenery. */
		m_ObjectsList.push_back(new Lever(TILE_32PX_TO_8PX(16), TILE_32PX_TO_8PX(22)));
	}
};


#endif /* SCENERY01_H_ */
