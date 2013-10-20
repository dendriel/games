/*
 * GameScenery.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMESCENERY_H_
#define GAMESCENERY_H_

#include <vector>
#include "GameMap.h"
#include "GameObject.h"

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

	//< Fill with all the objects from the game.
	std::vector<GameObject *> m_ObjectsList;

public:

	/**
	 * \brief Touch items on the scenery.
	 * \parameter touching The touching points to be verified.
	 */
	void check_touch_points(st_offset touching[]);

	/**
	 * \brief Verify if the point is touching the area.
	 * \parameter touching The touching point.
	 * \parameter area The area to verify.
	 * \return true if the area is being touched; false otherwise.
	 */
	bool check_touched_object(st_offset touching, st_rect area);

	virtual ~GameScenery(void)
	{
		;;
	}

	/**
	 * \brief Add the objects from the scenery.
	 */
	virtual void fill_objects_list(void)
	{
		;;
	}

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
