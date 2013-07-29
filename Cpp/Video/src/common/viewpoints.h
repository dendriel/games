/*
 * viewpoints.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef VIEWPOINTS_H_
#define VIEWPOINTS_H_

#include "SDL/SDL.h"
#include <string>

using namespace std;

typedef enum {
	IMAGE_DOWN_STAND = 0,
	IMAGE_DOWN_RIGHT,
	IMAGE_DOWN_LEFT,
	IMAGE_RIGHT_STAND,
	IMAGE_RIGHT_RIGHT,
	IMAGE_RIGHT_LEFT,
	IMAGE_LEFT_STAND,
	IMAGE_LEFT_RIGHT,
	IMAGE_LEFT_LEFT,
	IMAGE_UP_STAND,
	IMAGE_UP_RIGHT,
	IMAGE_UP_LEFT
} en_image_viewpoints;

#define DEFAULT_TILESET_SOURCE "image/basic_tileset_128x128.bmp"

/**
 * \brief Build a viewpoint array from the raw image.
 * \param source The raw image that will be used as data source.
 * \param position Number of positions in the source.
 * \param views Number of views per positions.
 * \param viewpoints The array that will be filled.
 * \return 0 if successfully filled the array; -1 if any error has occurred.
 */
int build_viewpoints(const char *source, const unsigned int positions, const unsigned int views, SDL_Surface **viewpoints);

/**
 * \brief Build the scenery view.
 * \return 0 for success; -1 for error.
 */
int build_mapview(SDL_Surface **mapview, const SDL_Rect& size, const string& source=DEFAULT_TILESET_SOURCE);

#endif /* VIEWPOINTS_H_ */
