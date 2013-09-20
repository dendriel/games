/*
 * convConversor.h
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#ifndef CONVCONVERSOR_H_
#define CONVCONVERSOR_H_

#include <iostream>

#include "util.h"

/* Definitions */
#define DATA_WIDTH 4
#define DATA_HEIGHT 4
#define TILE_DATA_SIZE DATA_WIDTH*DATA_HEIGHT


/**
 * \brief Data conversor class.
 */
class convConversor {

public:
	/**
	 * \brief Testing purpose function.
	 */
	void print_tile(const unsigned int origin_offset_in_memb, const unsigned int map_width, const unsigned short *data);

	/**
	 * \brief Convert an integer map array to an 8x8 tiled map array.
	 * \parameter origin Integer origin map.
	 * \parameter dest Reference where the output map will be stored.
	 */
	void convert(const st_map_bg&  origin, st_map_data& dest);

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

private:
	/**
	 * \brief Allocate and initialize enough data to hold the output map.
	 * \parameter data Where to hold the allocated data.
	 * \parameter size_in_tiles The size of the origin map.
	 * \return The total size of the allocated data chunk.
	 */
	size_t create_map(unsigned short **data, const size_t size_in_tiles);

	/**
	 * \brief Copy a tile from tileset to destination map data.
	 * \parameter tileset_offset Tileset data offset.
	 * \parameter tileset Tileset reference.
	 * \parameter dest_offset Destination data offset.
	 * \parameter dest Data reference.
	 */
	void copy_tile(const unsigned int tileset_width,
					const unsigned short *tileset,
					const unsigned int dest_width,
					unsigned short* dest);

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
