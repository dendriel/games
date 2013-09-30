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
	st_rect_size m_LoadedMap_data_offset;	//!< Map offset to copy data (in tiles 32x32).
	st_rect_size m_ScrollOffset;			//!< Screen scrolling bounds and current offset (in px).

public:

	/**
	 * \brief Class constructor.
	 */
	GameMapProcessor(void);

	/**
	 * \brief Load the given map into the game.
	 * \parameter map Map to be loaded.
	 * \parameter x Starting horizontal position of the map.
	 * \parameter y Starting vertical position of the map.
	 * \note First form will use the own map specified starting point.
	 */
	void load_Map(GameMap *map);
	void load_Map(GameMap *map, const int x, const int y);

	/**
	 * \brief Scroll all the background layers by x,y offset.
	 * \parameter x Horizontal offset.
	 * \parameter x Vertical offset.
	 * \note Scroll when it's possible, load data by demand.
	 */
	void scroll_Background(const int x, const int y);

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
	 * \brief Load map data with the addition of an offset.
	 * \parameter direction Wich direction is the data offset.
	 * \return 0 if the data was loaded; -1 if there is no more data to the given direction.
	 */
	int load_MapData(en_direction direction);

};

#endif /* GAMEMAPPROCESSOR_H_ */
