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

#include "SDL.h"

#include "GameSprite.h"

class Spritesheet
{
	SDL_Texture *_texture;
	std::map <std::string, GameSprite *> sprite_list;

public:
	Spritesheet(std::string texture_name="", SDL_Renderer *renderer=NULL);
	virtual ~Spritesheet();

	void add(std::string filename,
			SDL_Rect frame,
			bool rotated,
			bool trimmed,
			SDL_Rect sprite_source_size,
			SDL_Rect source_size,
			SDL_Rect pivot,
			unsigned int id); // id = numeric identification.

	GameSprite *getSprite(const std::string name);
	GameSprite *getSprite(const unsigned int id);

	/**
	 * @brief Load the spritesheet texture.
	 */
	void setTexture(std::string texture_name, SDL_Renderer *renderer);

	/**
	 * @brief Get texture.
	 */
	SDL_Texture *texture(void);

	/**
	 * @brief Print all sprites information. Debugging purpose.
	 */
	void dump(void);
};

#endif /* SPRITESHEET_H_ */
