/*
 * Maze1_mp.h
 *
 *  Created on: 24/09/2013
 *      Author: vitor
 */

#ifndef MAZE1_MP_H_
#define MAZE1_MP_H_


#include "Map.h"
#include "maze1_data.h"

class Maze1_mp: public virtual Map {
public:
	/**
	 * \brief Class constructor.
	 */
	Maze1_mp(void)
	{
		tiles_map = maze1_Map;
		//!< Length in tiles.
		len_tiles = maze1_LenTiles;
		//!< Width in tiles.
		width_tiles = maze1_WidthTiles;
		//!< Height in tiles.
		height_tiles = maze1_HeightTiles;
	}
};

#endif /* MAZE1_MP_H_ */
