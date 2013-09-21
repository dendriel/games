/*
 * convConversor.h
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#ifndef CONVCONVERSOR_H_
#define CONVCONVERSOR_H_

#include <iostream>

#include "Tileset.h"
#include "Map.h"
#include "util.h"

/* Definitions */
#define DATA_WIDTH 4
#define DATA_HEIGHT 4
#define TILE_LEN_MEMB DATA_WIDTH*DATA_HEIGHT


/**
 * \brief Data conversor class.
 */
class convConversor {

public:
	/**
	 * \brief Testing purpose function.
	 */
	void print_tile(const unsigned int origin_offset_in_memb,
			const unsigned int map_width_tiles,
			const unsigned short *data);

	/**
	 * \brief Convert an integer map array to an 8x8 tiled map array.
	 * \parameter origin Integer origin map.
	 * \parameter dest Reference where the output map will be stored.
	 */
	void convert(Map& origin, st_map_data& dest, Tileset& tileset);

	/**
	 * \brief Find total offset for a position.
	 * \parameter pos The position in a unidimensional array.
	 * \parameter map_width The size of each row in the matrix map view.
	 * \return The total data offset.
	 */
	inline unsigned int find_total_offset(const unsigned int pos, const unsigned int map_width)
	{
		return find_h_offset(pos, map_width) + find_v_offset(pos, map_width);
	}

	/**
	 * \brief Allocate and initialize enough data to hold the output map.
	 * \parameter data Where to hold the allocated data.
	 * \parameter size_in_tiles The size of the origin map.
	 * \return The total size of the allocated data chunk.
	 */
	void create_map(Map& origin, st_map_data& dest);
	
private:
	/**
	 * \brief Copy a tile from tile set to destination map data.
	 * \parameter tileset Tile set reference.
	 * \parameter tileset_offset Tile set data offset.
	 * \parameter dest Destination data reference.
	 * \parameter dest_offset Destination data offset.
	 */
	void copy_tile(
			st_map_data& dest,
			const unsigned int dest_offset_memb,
			Tileset& tileset,
			const unsigned int tileset_offset_memb);
	
	/**
	 * \brief Find horizontal offset for a position.
	 * \parameter pos The position in a unidimensional array.
	 * \parameter map_width The size of each row in the matrix map view.
	 * \return The horizontal offset.
	 */
	inline int find_h_offset(const unsigned int pos, const unsigned int map_width)
	{
		return (pos - (pos / map_width) * map_width) * DATA_WIDTH;
	}

	/**
	 * \brief Find vertical offset for a position.
	 * \parameter pos The position in a unidimensional array.
	 * \parameter map_width The size of each row in the matrix map view.
	 * \return The vertical offset.
	 */
	inline int find_v_offset(const unsigned int pos, const unsigned int map_width)
	{
		return ((pos / map_width) * map_width * DATA_WIDTH * DATA_HEIGHT);
	}
};

#endif /* CONVCONVERSOR_H_ */
