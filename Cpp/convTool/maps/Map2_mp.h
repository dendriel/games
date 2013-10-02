#ifndef MAP2_MP_H_
#define MAP2_MP_H_

#include "Map.h"
#include "map2_data.h"

class Map2_mp: public virtual Map {
public:
	/**
	 * \brief Class constructor.
	 */
	Map2_mp(void)
	{
		tiles_map = map2_Map;
		//!< Length in tiles.
		len_tiles = map2_LenTiles;
		//!< Width in tiles.
		width_tiles = map2_WidthTiles;
		//!< Height in tiles.
		height_tiles = map2_HeightTiles;
	}
};

#endif /*MAP2_MP_H_*/
