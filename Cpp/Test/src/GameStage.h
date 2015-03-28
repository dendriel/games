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
	int _player_id;
	int _ground_id;
	int _target_id;
	int _box_id;
	std::string _player_sprite;
	std::string _target_sprite;
	std::string _box_sprite;

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

	inline int player_id(void)
	{
		return _player_id;
	}

	inline int ground_id(void)
	{
		return _ground_id;
	}

	inline int box_id(void)
	{
		return _box_id;
	}

	inline int target_id(void)
	{
		return _target_id;
	}

	inline std::string player_sprite(void)
	{
		return _player_sprite;
	}

	inline std::string target_sprite(void)
	{
		return _target_sprite;
	}

	inline std::string box_sprite(void)
	{
		return _box_sprite;
	}
};

#endif /* GAMESTAGE_H_ */
