#ifndef MAP1_MP_H_
#define MAP1_MP_H_

#include "Map.h"
#include "map1_data.h"

class Map1_mp: public virtual Map {
public:
	/**
	 * \brief Class constructor.
	 */
	Map1_mp(void)
	{
		tiles_map = map1_Map;
		//!< Length in tiles.
		len_tiles = map1_LenTiles;
		//!< Width in tiles.
		width_tiles = map1_WidthTiles;
		//!< Height in tiles.
		height_tiles = map1_HeightTiles;
	}
};

#endif /*MAP1_MP_H_*/
