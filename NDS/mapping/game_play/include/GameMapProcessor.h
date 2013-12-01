/*
 * GameMapProcessor.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef GAMEMAPPROCESSOR_H_
#define GAMEMAPPROCESSOR_H_

#include <nds.h>

#include "GameMap.h"
#include "util.h"

/* Suffixes for parameters:
 *
 *   _px = variable amount of pixels.
 *  _8px = tiles of 8 pixels.
 *  tiles = tiles of 32 pixels.
 *
 *  If the own function have the suffix, there is no need to put it in the parameter.
 */

/**
 *	\brief Generic direction enumeration.
 */
typedef enum {
	DIRECT_NONE= 0,
	DIRECT_LEFT,
	DIRECT_UP,
	DIRECT_RIGHT,
	DIRECT_DOWN
} en_direction;

/**
 *	\brief Hold screen and mapping issues.
 */
class GameMapProcessor {
private:
	GameMap *m_LoadedMap;					//!< Loaded map object reference.
	st_offset m_LoadedMap_offset_8px;		//!< The position of the map. Also used to load it.
	st_offset m_LoadedMap_bounds_8px;		//!< Loaded map bounds.
	unsigned int m_AnimatedLayer_cooldown;	//!< Cooldown for layer animation.

public:

	/**
	 * \brief Class constructor.
	 */
	GameMapProcessor(void);

	/**
	 * \brief Clean Map Processor resources (initialization and re-initialization).
	 */
	void clean_resources(void);

	/**
	 * \brief Scroll all the background layers by x, y offset.
	 * \parameter x Horizontal offset.
	 * \parameter y Vertical offset.
	 * \note Scroll when it's possible, load data by demand.
	 * \return 0 if the could scroll the background;
	 * -1 if there is no more background to load.
	 */
	int move_map_8px(const int x, const int y);

	/**
	 * \brief Check if the next move is a static.
	 * \parameter x Horizontal offset.
	 * \parameter y Vertical offset.
	 * \return 0 can make the move; 1 if the path is blocked.
	 */
	int check_static_collision_px(const int x, const int y);

	/**
	 * \brief Verify if the coordinates (relative position) are inside a collision position of the
	 * static domain.
	 * \parameter rect_elem Rectangle data. All bounds will be checked and will return at the first
	 * collision occurrence.
	 * \parameter x_px Horizontal position to check in pixels.
	 * \parameter y_px Vertical position to check in pixels.
	 * \return True if collision was detected; False if is not a collision.
	 */
	bool check_static_collision(st_rect& rect_elem);

	/**
	 * \brief Scroll all the background layers by x, y in TILES.
	 * \parameter x Horizontal offset.
	 * \parameter y Vertical offset.
	 */
	void move_map_32px(const int x, const int y);

	/**
	 * \brief Update the map (draw the map animated frames).
	 */
	void update(void);

	void operator<<(GameMap *map)
	{
		this->load_Map(map);
	}

private:

	/**
	 * \brief Load the given map into the game.
	 * \parameter map Map to be loaded.
	 * \note Initial offset must be made separately.
	 */
	void load_Map(GameMap *map);

	/**
	 * \brief Draw the loaded map into the screen.
	 * 
	 * 
	 * Layer 0 = base layer;
	 * Layer 1 = objects layer;
	 * Layer 2 = animated 1;
	 * Layer 3 = unused;
	 * 
	 */
	void draw_LoadedMap(void);

	/**
	 * \brief Copy data to a quarter of the screen
	 * \parameter screen_quarter What screen quarter to draw.
	 * \parameter origin The background data to copy.
	 * \parameter dest A reference to the destination.
	 */
	void draw_LayerQuarter(
		const en_screen_quarter screen_quarter,
		const unsigned short *origin,
		u16 *dest);

	/**
	 * \brief Load 8 pixels of map data with the addition of an offset.
	 * \parameter direction Wich direction is the data offset.
	 * \return 0 if the data was loaded; -1 if there is no more data to the given direction.
	 */
	int load_MapData_8px(en_direction direction);
	
	/**
	 * \brief Get cooldown before next layer animation.
	 */
	inline int get_animated_layer_cooldown(void)
	{
		return m_AnimatedLayer_cooldown;
	}

	/**
	 * \brief Set cooldown before next layer animation.
	 */
	inline void set_animated_layer_cooldown(unsigned int value)
	{
		m_AnimatedLayer_cooldown = value;
	}

	/**
	 * \brief Update cooldown before next layer animation.
	 */
	inline void update_animated_layer_cooldown(void)
	{
		if (m_AnimatedLayer_cooldown > 0) {
			m_AnimatedLayer_cooldown--;
		}
	}

};

#endif /* GAMEMAPPROCESSOR_H_ */
