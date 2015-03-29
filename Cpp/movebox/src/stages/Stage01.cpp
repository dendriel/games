/*
 * Stage01.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#include "Stage01.h"

#include <iostream>

static int Map[] =  {
		0,0,3,3,3,0,0,0,
		0,0,3,2,3,0,0,0,
		0,0,3,1,3,3,3,3,
		3,3,3,5,1,5,2,3,
		3,2,1,5,4,3,3,3,
		3,3,3,3,5,3,0,0,
		0,0,0,3,2,3,0,0,
		0,0,0,3,3,3,0,0};

Stage01::Stage01(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 8;
	_map_size.h = 8;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage01::~Stage01()
{
	_map_arr = NULL;
}

