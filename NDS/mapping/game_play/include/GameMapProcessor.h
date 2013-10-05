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
	 * \brief Load the given map into the game.
	 * \parameter map Map to be loaded.
	 * \note Initial offset must be made separately.
	 */
	void load_Map(GameMap *map);

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
	 * \brief Scroll all the background layers by x, y in TILES.
	 * \parameter x Horizontal offset.
	 * \parameter y Vertical offset.
	 */
	void move_map_32px(const int x, const int y);

private:

	/**
	 * \brief Draw the loaded map into the screen.
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

};

#endif /* GAMEMAPPROCESSOR_H_ */
