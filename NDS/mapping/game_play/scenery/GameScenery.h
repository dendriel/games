/*
 * GameScenery.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMESCENERY_H_
#define GAMESCENERY_H_

#include "GameMap.h"

/**
 * \brief Hold all data from a scenery.
 */
class GameScenery {
protected:
	//!< Scenery map data.
	GameMap *m_Map;
	//!< Character starting point in tiles (Relative position).
	st_offset m_CharStartPoint_tiles;
	// StaticCollisionDomain
	// DynamicCollisionDomain

public:

	inline GameMap *get_Map(void)
	{
		return m_Map;
	}

	inline int get_CharStartPoint_x(void)
	{
		return m_CharStartPoint_tiles.x;
	}

	inline int get_CharStartPoint_y(void)
	{
		return m_CharStartPoint_tiles.y;
	}
};

#endif /* GAMESCENERY_H_ */
