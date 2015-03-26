/*
 * Utils.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include "SDL.h"

class Utils
{
public:
	Utils();
	virtual ~Utils();

	static SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);
};

#endif /* UTILS_H_ */
