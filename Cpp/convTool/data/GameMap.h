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
	//!< How much layers there is in the map.
	size_t m_LayersCount;

	//!< Hold backgrounds data.
	st_map_bg m_Background[MAX_MAP_BACKGROUNDS];

	//!< Character starting point. TODO: maybe this data will be in a more embracing class.
	st_offset m_CharStartPoint;
};


#endif /* GAMEMAP_H_ */
