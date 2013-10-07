#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>

/**
 * \brif Map data base class.
 */
class Map {
public:
	//!< Tiles position.
	const unsigned int *tiles_map;
	//!< Length in tiles.
	size_t len_tiles;
	//!< Width in tiles.
	size_t width_tiles;
	//!< Height in tiles.
	size_t height_tiles;
};

#endif /*MAP_H_*/
