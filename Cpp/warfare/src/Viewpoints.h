/*
 * Viewpoints.h
 *
 *  Created on: 15/05/2014
 *      Author: vitor
 */

#ifndef VIEWPOINTS_H_
#define VIEWPOINTS_H_

#include <string>
#include "SDL/SDL.h"

//!< Represents a cartographic position.
typedef struct {
	int x;
	int y;
} st_element_pos;

//!< Define color keys.
#define RED 255
#define GREEN 0
#define BLUE 255
#define BPP 32

class Viewpoints {
public:
	/*
	 * Constructor.
	 */
	Viewpoints();

	/*
	 * Destructor.
	 */
	virtual ~Viewpoints();

	/**
	 * \brief Build a viewpoint array from the raw image.
	 * \param source The raw image that will be used as data source.
	 * \param position Number of positions in the source.
	 * \param views Number of views per positions.
	 * \param viewpoints The array that will be filled.
	 * \return 0 if successfully filled the array; -1 if any error has occurred.
	 */
	static int build_viewpoints(const char *source,
			const unsigned int positions,
			const unsigned int views,
			SDL_Surface **viewpoints);

	/**
	 * \brief Build a scenery layer.
	 * \param layer The surface that will contain the builded layer.
	 * \param layer_bounds Contain the matrix maximum x and y.
	 * \param tile_list The tile array.
	 * \param tile_size Size of the tile to be blit from the source image.
	 * \param source The tile set data source.
	 * \return 0 for success; -1 for error.
	 */
	static int build_layer(SDL_Surface **layer,
			const st_element_pos layer_bounds,
			const unsigned int *tile_list,
			st_element_pos& tile_size,
			const std::string& source);


	/**
	 * \brief Build a scenery layer.
	 * \param layer The surface that will contain the builded layer.
	 * \param layer_bounds Contain the matrix maximum x and y.
	 * \param tile_list The tile array.
	 * \param source The tile set data source.
	 * \return 0 for success; -1 for error.
	 */
	static int build_layer_hex(SDL_Surface **layer,
			const st_element_pos layer_bounds,
			const unsigned int *tile_list,
			const std::string& source,
			const st_element_pos tile_size);
};

#endif /* VIEWPOINTS_H_ */
