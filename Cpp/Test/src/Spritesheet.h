/*
 * Spritesheet.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <string>
#include <map>

#include "GameSprite.h"

class Spritesheet
{
	std::string source_filename;
	std::map <std::string, GameSprite *> sprite_list;
	SDL_Texture *_texture;

public:
	Spritesheet();
	virtual ~Spritesheet();

	void add(std::string filename,
			SDL_Rect frame,
			bool rotated,
			bool trimmed,
			SDL_Rect sprite_source_size,
			SDL_Rect source_size,
			SDL_Rect pivot);

	GameSprite *getSprite(std::string name);

	void setTexture(SDL_Texture *texture);

	SDL_Texture *texture(void);

	void dump(void);
};

#endif /* SPRITESHEET_H_ */
