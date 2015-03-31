/*
 * GameAtlas.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef GAMEATLAS_H_
#define GAMEATLAS_H_

#include <vector>
#include <string>

#include "Spritesheet.h"

/**
 * Hold sprite sheet information.
 */
class GameAtlas
{
	std::vector<Spritesheet *> sheet_list;
	std::map<std::string, SDL_Texture *> texture_list;

public:
	GameAtlas();
	virtual ~GameAtlas();

	/**
	 * @brief Add a spriteeshet to the Atlas.
	 * WARNING: The atlas will not free the spriteshets in order to avoid double free.
	 */
	void addSheet(Spritesheet *sheet);

	/**
	 * @brief Remove all sheets from atlas.
	 */
	void clearAllSheets(void);

	/**
	 * @brief Look for the sheet that owns the given sprite.
	 */
	Spritesheet *getSheet(const std::string name);
	Spritesheet *getSheet(const int id);

	/**
	 * @brief Load a texture in the atlas.
	 */
	void addTexture(const std::string name, SDL_Renderer *renderer);

	/**
	 * @brief Use a texture from the atlas.
	 */
	SDL_Texture *getTexture(const std::string name);
};

#endif /* GAMEATLAS_H_ */
