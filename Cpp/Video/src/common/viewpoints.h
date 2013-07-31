/*
 * viewpoints.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef VIEWPOINTS_H_
#define VIEWPOINTS_H_

#include "viewpoints_defines.h"

#include <string>

#include "SDL/SDL.h"

using namespace std;

/**
 * \brief Build a viewpoint array from the raw image.
 * \param source The raw image that will be used as data source.
 * \param position Number of positions in the source.
 * \param views Number of views per positions.
 * \param viewpoints The array that will be filled.
 * \return 0 if successfully filled the array; -1 if any error has occurred.
 */
int build_viewpoints(const char *source,
		const unsigned int positions,
		const unsigned int views,
		SDL_Surface **viewpoints);

/**
 * \brief Build a scenery layer.
 * \param layer The surface that will contain the builded layer.
 * \param layer_bounds Contain the matrix maximum x and y.
 * \param tile_list The tile array.
 * \param source The tile set data source.
 * \return 0 for success; -1 for error.
 */
int build_layer(SDL_Surface **layer,
		const st_element_pos layer_bounds,
		const unsigned int *tile_list,
		const string& source=TILESET_SOURCE);

#endif /* VIEWPOINTS_H_ */
