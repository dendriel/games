/*
 * convConversor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#include "convConversor.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************/

void convConversor::convert(Map& origin, st_map_data& dest, Tileset& tileset)
{
	/* For each tile found in origin. */
	for (size_t tile_pos = 0; tile_pos < origin.len_tiles; ++tile_pos) {

		/* Mappy win32 set tile set 0 as transparent, so, we start counting by 1
		 * Edit: Removing the offset when reading from the file.
		 */
		const unsigned int tile_id = origin.tiles_map[tile_pos];

		/* Find "from" position to copy. */
		const size_t tileset_offset = find_total_offset(tile_id, tileset.map_width_tiles);
		
		/* Find "to" position to copy. */
		const size_t dest_offset = find_total_offset(tile_pos, origin.width_tiles);

		/* Convert. */
		copy_tile(dest, dest_offset, tileset, tileset_offset);
	}
}

/**************************************************************************************************/

void convConversor::print_tile(
		const unsigned int origin_offset_in_memb,
		const unsigned int map_width_tiles,
		const unsigned short *data)
{
	cout << showbase << internal << setfill('0');

	for (unsigned int i = 0; i < DATA_HEIGHT; ++i) {

		const unsigned int height_offset = origin_offset_in_memb + (map_width_tiles * DATA_WIDTH * i);

		for (unsigned width_offset = 0; width_offset < DATA_WIDTH; ++width_offset) {

			const unsigned int origin_data_pos = height_offset + width_offset;
			cout << hex << setw(4) << data[origin_data_pos] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void convConversor::create_map(Map& origin, st_map_data& dest)
{
	/**
	 * Need to allocated tiles of size of 4x4 plus the unsigned short size (2).
	 */
	dest.lenght_memb = origin.len_tiles*TILE_LEN_MEMB;;
	dest.width_memb = origin.width_tiles*DATA_WIDTH;
	dest.height_memb = origin.height_tiles*DATA_HEIGHT;
	dest.data = (unsigned short *) calloc(dest.lenght_memb, sizeof(unsigned short));
	
	assert(dest.data != NULL);

	/* Lenght in bytes would be to_alloc*sizeof(unsigned short)*/
	//cout << "cAllocated " << dest.lenght_memb*sizeof(unsigned short) << " bytes for dest data." << endl;
}

/**************************************************************************************************/
/*	Private functions.																			*/
/**************************************************************************************************/

void convConversor::copy_tile(
		st_map_data& dest,
		const unsigned int dest_offset_memb,
		Tileset& tileset,
		const unsigned int tileset_offset_memb)
{
	for (unsigned int vert = 0; vert < DATA_HEIGHT; ++vert) {
		/* Vertical offset */
		unsigned int tileset_index = (tileset.map_width_tiles * DATA_WIDTH * vert) + tileset_offset_memb;
		unsigned int dest_index    = (dest.width_memb * vert) + dest_offset_memb;

		memcpy(&dest.data[dest_index],
				&tileset.map[tileset_index],
				DATA_WIDTH*sizeof(unsigned short));
	}
	//print_tile(dest_offset_memb, dest.width_memb/4, dest.data);
}

