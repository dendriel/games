/*
 * convConversor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#include "convConversor.h"

#include <stdlib.h>
#include <string.h>

using namespace std;

/**************************************************************************************************/

void convConversor::convert(st_map_data& origin, st_map_data& dest, st_map_data& tileset)
{
	unsigned int i;

	/* Create expanded destination map. */
	dest.lenght = create_map(&dest.ushort_data, origin.lenght);
	dest.size.w = origin.size.w*DATA_WIDTH;
	dest.size.h = origin.size.h*DATA_WIDTH;

	for (i = 0; i < origin.lenght; ++i) {
		const unsigned int tile_id = origin.uint_data[i];

		/* Find "from" position to copy. */
		unsigned int tileset_offset = find_total_offset(tile_id, tileset.size.w);
		/* Validate index. */
		if (tileset_offset > (tileset.lenght - TILE_DATA_SIZE)) {
			tileset_offset = tileset.lenght - TILE_DATA_SIZE;
		}

		/* Find "to" position to copy. */
		const unsigned int dest_offset = find_total_offset(i, origin.size.w);

		copy_tile(tileset.size.w, (tileset.cushort_data + tileset_offset/2),
					dest.size.w, (dest.ushort_data + dest_offset/2));
		cout << "i: " << i << " - tileset_offset: " << tileset_offset << endl;
		cout << "i: " << i << " - dest_offset: " << dest_offset << endl << endl;;
		// draw what
		// draw where
		//convert_index(tile_id, dest.data)
	}
	/* Find the starting point to draw data. */
}

/**************************************************************************************************/

void convConversor::print_tile(const unsigned int origin_offset, const unsigned int map_width)
{
#if 0
	unsigned int i, j;

	for (i = 0; i < DATA_HEIGHT; ++i) {

		const unsigned int height_offset = origin_offset + (map_width * DATA_WIDTH * i);

		for (unsigned width_offset = 0; width_offset < DATA_WIDTH; ++width_offset) {

			const unsigned int origin_data_pos = height_offset + width_offset;

			//std::cout << mytiles_map[origin_data_pos] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
#endif
}

/**************************************************************************************************/
/*	Private functions.																			*/
/**************************************************************************************************/

size_t convConversor::create_map(unsigned short **data, const size_t size)
{
	const unsigned int to_alloc = size*DATA_WIDTH*DATA_HEIGHT;
	*data = (unsigned short *) calloc(to_alloc, sizeof(char));
	return to_alloc;
}

/**************************************************************************************************/

void convConversor::copy_tile(const unsigned int tileset_width,
				const unsigned short *tileset,
				const unsigned int dest_width,
				unsigned short *dest)
{
	unsigned int horiz, vert;

	for (vert = 0; vert < DATA_HEIGHT; ++vert) {
		/* Vertical offset */
		tileset += vert*DATA_WIDTH*tileset_width;
		dest += vert*DATA_WIDTH*dest_width;

		for (horiz = 0; horiz < DATA_WIDTH; ++horiz) {
			/* Horizontal offset. */
			tileset += horiz;
			dest += horiz;
			cout << "vert: " << vert << " - horiz: " << horiz << endl;
			cout << "tileset: " << tileset << " - dest: " << dest << endl;
			memcpy(dest, tileset, sizeof(unsigned short));
		}
	}
}

