/*
 * Scenery01.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef SCENERY01_H_
#define SCENERY01_H_

#include "GameScenery.h"
#include "Maze3.h"
#include "Maze2.h"

class Scenery01: public GameScenery {
public:
	/**
	 * \brief Class constructor.
	 */
	Scenery01(void)
	{
		m_Map = new Maze3;
		m_CharStartPoint_tiles.x = 10;
		m_CharStartPoint_tiles.y = 10;
	}

	/**
	 * \brief Class destructor.
	 */
	~Scenery01(void)
	{
		delete(m_Map);
	}
};


#endif /* SCENERY01_H_ */
