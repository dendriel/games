/*
 * Stage01.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#include "Stage01.h"

#include <iostream>

static int Map[] =  {0, 0, 3, 3, 3, 3, 3,
					 3, 3, 3, 1, 2, 1, 3,
					 3, 1, 1, 4, 5, 2, 3,
					 3, 1, 5, 3, 1, 1, 3,
					 3, 1, 1, 3, 3, 3, 3,
					 3, 3, 3, 3, 0, 0, 0};

Stage01::Stage01(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 7;
	_map_size.h = 6;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage01::~Stage01()
{
	_map_arr = NULL;
}

