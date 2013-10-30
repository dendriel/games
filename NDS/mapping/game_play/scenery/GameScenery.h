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

#include "util.h"

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

	inline std::vector<GameObject *> *get_ObjectsList(void)
	{
		return &m_ObjectsList;
	}

	/**
	 * \brief Get an object reference from the list pointed by its id.
	 * return The object reference if found; or NULL if the object was not found in the list.
	 */
	inline GameObject *get_Object(const long id)
	{
		for(std::vector<GameObject *>::iterator iter = m_ObjectsList.begin();
				iter != m_ObjectsList.end(); ++iter) {
			GameObject *object = *iter;
			if (object->get_Id() == id) {
				return object;
			}
		}
		return NULL;
	}

	/**
	 * \brief Removes (but don't destroy) an object reference from the list pointed by its id.
	 */
	inline void remove_Object(const long id)
	{
		for(std::vector<GameObject *>::iterator iter = m_ObjectsList.begin();
				iter != m_ObjectsList.end(); ++iter) {
			GameObject *object = *iter;
			if (object->get_Id() == id) {
				m_ObjectsList.erase(iter);
				debug("scen objs: %d", m_ObjectsList.size());
			}
		}
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
