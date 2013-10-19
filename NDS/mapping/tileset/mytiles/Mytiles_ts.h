#ifndef MYTILES_TS_H_
#define MYTILES_TS_H_

#include "Tileset.h"
#include "mytiles_tileset_data.h"

/**
 * \brief Mytiles tile set.
 */
class Mytiles_ts: public virtual Tileset {
public:
	/**
	 * \brief Class constructor. Fill up all data.
	 */
	Mytiles_ts(void)
	{
		map = mytiles_map;
		map_width_tiles = mytiles_width_tiles;
		map_height_tiles = mytiles_height_tiles;
		
		collision_map = mytiles_collision_map;

		data = mytiles_sharedTiles;
		data_len_bytes = mytiles_sharedTilesLen_bytes;
		
		pallete = mytiles_sharedPal;
		pallete_len_bytes = mytiles_sharedPalLen_bytes;
	}
};

#endif /*MYTILES_TS_H_*/
