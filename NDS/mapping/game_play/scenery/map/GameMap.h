/*
 * GameMap.h
 *
 *  Created on: 08/09/2013
 *      Author: vitor
 */

#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include <stdio.h>

#include "util.h"

/* Definitions */
#define MAX_MAP_BACKGROUNDS 4


class GameMap {
public:
	//!< Map size in tiles 8px.
	st_offset m_SizeTile_8px;
	
	//!< Map size in tiles 32x32 px.
	st_offset m_SizeTile_32px;

	//!< How much layers there is in the map.
	size_t m_LayersCount;

	//!< Hold backgrounds data.
	st_map_bg m_Background[MAX_MAP_BACKGROUNDS];

	//!< Hold the tiles palette for every background.
	const unsigned int *m_Tiles;

	//!< Hold the tiles length.
	size_t m_TilesLen;

	//!< Background palette.
	const unsigned short *m_Palette;

	//!< Background palette length.
	size_t m_PaletteLen;
};


#endif /* GAMEMAP_H_ */
