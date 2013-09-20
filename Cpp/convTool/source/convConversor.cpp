/*
 * convConversor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#include "convConversor.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

/**************************************************************************************************/

void convConversor::convert(const st_map_bg& origin, st_map_data& dest)
{
	size_t i;

	/* Create expanded destination map. */
	dest.length_memb = create_map(&dest.ushort_data, origin.width_tiles*origin.height_tiles);
	dest.size_tiles.w = origin.width_tiles*DATA_WIDTH;
	dest.size_tiles.h = origin.height_tiles*DATA_HEIGHT;

	const size_t origin_len_tiles = origin.width_tiles*origin.height_tiles;

	debug("Allocated: %hu of ushorts.\n Origin length in tiles: %d\n", dest.length_memb, origin_len_tiles);

	for (i = 0; i < origin_len_tiles; ++i) {

		const unsigned int tile_id = origin.data[i];

		/* Find "from" position to copy. */
		unsigned int tileset_offset = find_total_offset(tile_id, origin.tileset.dim_tiles.w);

		/* Validate index. */
		if (tileset_offset > (origin.tileset.len_memb - TILE_DATA_SIZE)) {
			tileset_offset = origin.tileset.len_memb - TILE_DATA_SIZE;
		}

		/* Find "to" position to copy. */
		const unsigned int dest_offset = find_total_offset(i, origin.width_tiles);

		copy_tile(origin.tileset.dim_tiles.w, (origin.tileset.map + tileset_offset),
					dest.size_tiles.w, (dest.ushort_data + dest_offset));

		cout << "[i] " <<i << " - tileset_offset: " << tileset_offset;
		cout << " - dest_offset: " << dest_offset << endl << endl;
		print_tile(dest_offset, dest.size_tiles.w, dest.ushort_data);
		cout << endl;
	}
}

/**************************************************************************************************/

void convConversor::print_tile(const unsigned int origin_offset_in_memb, const unsigned int map_width, const unsigned short *data)
{

	unsigned int i;

	cout << showbase << internal << setfill('0');

	for (i = 0; i < DATA_HEIGHT; ++i) {

		const unsigned int height_offset = origin_offset_in_memb + (map_width * DATA_WIDTH * i);

		for (unsigned width_offset = 0; width_offset < DATA_WIDTH; ++width_offset) {

			const unsigned int origin_data_pos = height_offset + width_offset;

			//cout << "[" << height_offset << "," << width_offset << "]";
			cout << hex << setw(4) << data[origin_data_pos] << " ";
		}
		cout << std::endl;
	}
	cout << std::endl;
}

/**************************************************************************************************/
/*	Private functions.																			*/
/**************************************************************************************************/

size_t convConversor::create_map(unsigned short **data, const size_t size_in_tiles)
{
	/**
	 * Need to allocated tiles of size of 4x4 plus the unsigned short size (2).
	 */
	const unsigned int to_alloc = size_in_tiles*DATA_WIDTH*DATA_HEIGHT;
	*data = (unsigned short *) calloc(to_alloc, sizeof(unsigned short));
	return to_alloc;
}

/**************************************************************************************************/

void convConversor::copy_tile(
		const unsigned int tileset_width,
		const unsigned short *tileset,
		const unsigned int dest_width,
		unsigned short *dest)
{
	unsigned int vert;
	unsigned int tileset_index;
	unsigned int dest_index;

	cout << showbase << internal << setfill('0');

	for (vert = 0; vert < DATA_HEIGHT; ++vert) {
		/* Vertical offset */
		tileset_index = tileset_width * DATA_WIDTH * vert; // find vertical offset?
		dest_index    =    dest_width * DATA_WIDTH * vert;

		//cout << "vert_tileset: " << tileset_index << " - vert_dest: " << dest_index << endl;

		memcpy(&dest[dest_index], &tileset[tileset_index], DATA_WIDTH*sizeof(unsigned short));

		cout << hex << setw(4) << dest[dest_index] << ",";
		cout << hex << setw(4) << dest[dest_index+1] << ",";
		cout << hex << setw(4) << dest[dest_index+2] << ",";
		cout << hex << setw(4) << dest[dest_index+3] << "," << endl;
	}
}

