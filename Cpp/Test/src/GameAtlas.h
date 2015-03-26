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

public:
	GameAtlas();
	virtual ~GameAtlas();

	void addSheet(Spritesheet *sheet);
	/**
	 * @brief Look for the sheet that owns the given sprite.
	 */
	Spritesheet *getSheet(const std::string name);
	Spritesheet *getSheet(const int id);
};

#endif /* GAMEATLAS_H_ */
