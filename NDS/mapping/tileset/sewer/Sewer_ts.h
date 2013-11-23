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
#include "sewer_tileset_collision.h"

#define SEWER_TILESET_WIDTH 8
#define SEWER_TILESET_HEIGHT 8

class Sewer_ts: public virtual Tileset {
public:
	/**
	 * \brief Class constructor. Fill up all data.
	 */
	Sewer_ts(void)
	{
		map = sewer_tilesetMap;
		map_width_tiles = SEWER_TILESET_WIDTH;
		map_height_tiles = SEWER_TILESET_HEIGHT;

		data = sewer_tileset_dataSharedTiles;
		data_len_bytes = sewer_tileset_dataSharedTilesLen;

		pallete = sewer_tileset_dataSharedPal;
		pallete_len_bytes = sewer_tileset_dataSharedPalLen;

		collision_map = sewer_tileset_collision_map;
	}
};


#endif /* SEWER_TS_H_ */
