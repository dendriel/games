/*
 * Stage.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#ifndef GAMESTAGE_H_
#define GAMESTAGE_H_

#include <string>

#include <SDL.h>

#include "Spritesheet.h"

class GameStage
{
protected:
	std::string _texture_name;
	Spritesheet *_sheet;
	int *_map_arr;
	SDL_Rect _map_size;
	SDL_Rect _map_size_pixel;

public:
	GameStage();
	virtual ~GameStage();

	inline std::string texture_name(void)
	{
		return _texture_name;
	}

	inline Spritesheet *sheet(void)
	{
		return _sheet;
	}

	inline int *map_arr(void)
	{
		return _map_arr;
	}

	inline SDL_Rect map_size(void)
	{
		return _map_size;
	}

	inline SDL_Rect map_size_pixel(void)
	{
		return _map_size_pixel;
	}
};

#endif /* GAMESTAGE_H_ */
