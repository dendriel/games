/*
 * surface.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */
#include <iostream>
#include <assert.h>

#include "SDL/SDL.h"

#include "utils.h"

using namespace std;

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
 * on the endianness (byte order) of the machine.
 */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

#define RED 255
#define GREEN 0
#define BLUE 255

int build_viewpoints(const char *source, const unsigned int positions, const unsigned int views, SDL_Surface **viewpoints)
{
	SDL_Surface *image_source;
	SDL_Rect viewpoint_size;
	SDL_Surface* optimizedImage = NULL;
	SDL_Surface *viewpoint = NULL;
	unsigned int position;

	CHK_NULL(image_source = SDL_LoadBMP(source));

	viewpoint_size.h = image_source->h/positions;
	viewpoint_size.w = image_source->w/views;

	for (unsigned char p_index = 1; p_index <= positions; ++p_index) {

		for (unsigned char v_index = 1; v_index <= views; ++v_index) {

			CHK_NULL((viewpoint = SDL_CreateRGBSurface(SDL_SWSURFACE, viewpoint_size.w, viewpoint_size.h,
									32, rmask, gmask, bmask, amask)));

			SDL_SetColorKey(viewpoint , SDL_SRCCOLORKEY, SDL_MapRGB(viewpoint->format, RED, GREEN, BLUE));

			position = ((((p_index*views)-views) + v_index) -1); // (((p*vmax)-vmax)+v)-1
			viewpoint_size.x = viewpoint_size.w*(v_index-1);
			viewpoint_size.y = viewpoint_size.h*(p_index-1);;

			CHK_NULL((optimizedImage = SDL_DisplayFormat(viewpoint)));

			SDL_FreeSurface(viewpoint);

			CHK(SDL_BlitSurface(image_source, &viewpoint_size, optimizedImage, NULL), -1);
			viewpoints[position] = optimizedImage;
		}
	}

	return 0;
}
