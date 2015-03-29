/*
 * VisualElement.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include <string>

#include <SDL.h>

class GameSprite
{
public:
	// Original data.
	std::string filename;
	SDL_Rect frame;
	bool rotated;
	bool trimmed;
	SDL_Rect sprite_source_size;
	SDL_Rect source_size;
	SDL_Rect pivot;
	unsigned int id;

	GameSprite(std::string filename,
			SDL_Rect frame,
			bool rotated,
			bool trimmed,
			SDL_Rect sprite_source_size,
			SDL_Rect source_size,
			SDL_Rect pivot,
			unsigned int id);
	virtual ~GameSprite();
};

#endif /* GAMESPRITE_H_ */
