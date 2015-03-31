/*
 * Utils.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#include "Utils.h"

#include <iostream>

#include <assert.h>

#include "SDL_image.h"
#include "SDL_ttf.h"

using namespace std;


Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

SDL_Texture* Utils::loadTexture(std::string path, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture *texture = NULL;

	//Load image at specified path
	SDL_Surface *surface = IMG_Load(path.c_str());
	if( surface == NULL )
	{
		cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
		assert(0);
	}


	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == NULL)
	{
		cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError();
		assert(0);
	}

	// Get rid of old loaded surface
	SDL_FreeSurface(surface);

	return texture;
}

int Utils::alignMiddle(const int obj1_px, const int obj1_w, const int obj2_w)
{
	int ref_middle = obj1_px + ( (obj1_w / 2) + (obj1_w % 2) );
	return (ref_middle - ( (obj2_w / 2) + (obj2_w % 2) ));
}

bool Utils::checkInsideBounds(const int px, const int py, const int ax, const int ay, const int aw, const int ah)
{
	if ( (px < ax) || (px >= (ax + aw) ) )
	{
			return false;
	}
	else if ( (py < ay) || (py >= (ay + ah) ) )
	{
			return false;
	}

	return true;
}
