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
	/**
	 *  Character starting point in tiles (Relative position).
	 *  The minimum relative position can't be less than 4x3 tiles, that is the absolute position of the char.
	 *  Therefore, the maximum position can't be more than map_h_tiles-4 and map_v_tiles-3.
	 */
	st_offset m_CharStartPoint_32px;
	// StaticCollisionDomain
	// DynamicCollisionDomain

public:

	inline GameMap *get_Map(void)
	{
		return m_Map;
	}

	inline int get_CharStartPoint_x_32px(void)
	{
		return m_CharStartPoint_32px.x;
	}

	inline int get_CharStartPoint_y_32px(void)
	{
		return m_CharStartPoint_32px.y;
	}
};

#endif /* GAMESCENERY_H_ */
