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
