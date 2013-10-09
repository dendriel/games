#ifndef TILESET_H_
#define TILESET_H_

#include <stdio.h>

/**
 * \brief Tile set base class.
 */
class Tileset {
public:
	//! Tile set data mapping.
	const unsigned short *map;
	size_t map_width_tiles;
	size_t map_height_tiles;

	//! Collision info about the tiles.
	const unsigned int *collision_map;

	//! Tiles data.
	const unsigned int *data;
	size_t data_len_bytes;
	
	//! Tiles pallete.
	const unsigned short *pallete;
	size_t pallete_len_bytes;
	
};
#endif /*TILESET_H_*/
