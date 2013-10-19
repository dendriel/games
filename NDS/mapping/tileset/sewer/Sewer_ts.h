/*
 * Sewer_ts.h
 *
 *  Created on: 19/10/2013
 *      Author: vitor
 */

#ifndef SEWER_TS_H_
#define SEWER_TS_H_

#include "Tileset.h"
#include "sewer_tileset_data.h"

class Sewer_ts: public virtual Tileset {
public:
	/**
	 * \brief Class constructor. Fill up all data.
	 */
	Sewer_ts(void)
	{
		map = sewer_tileset_map;
		map_width_tiles = sewer_width_tiles;
		map_height_tiles = sewer_height_tiles;

		collision_map = sewer_tileset_collision_map;

		data = sewer_tilesetSharedTiles;
		data_len_bytes = sewer_tilesetSharedTilesLen_bytes;

		pallete = sewer_tilesetSharedPal;
		pallete_len_bytes = sewer_tilesetSharedPalLen_bytes;
	}
};


#endif /* SEWER_TS_H_ */
