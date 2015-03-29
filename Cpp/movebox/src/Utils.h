/*
 * Utils.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <iomanip>
#include <string>

#include "SDL.h"

#define DEBUG

#ifdef DEBUG
#define PREFIX "[debug]"
#define debug(_str) std::cout << PREFIX << " " << std::setw(25) << __FILE__ << ":" << std::setw(4) << __LINE__ << ": " << _str << std::endl
#define assert_exit(_str) debug(_str << " (Asserting...)"); assert(0)
#else
#define debug(...)
#define assert_exit(...) assert(0)
#endif

class Utils
{
public:
	Utils();
	virtual ~Utils();

	static SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);
};

#endif /* UTILS_H_ */
