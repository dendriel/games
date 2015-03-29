/*
 * Stage03.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#include "Stage03.h"

#include "Utils.h"

static int Map[] =  {
		3,3,3,3,3,0,0,0,0,
		3,1,1,1,3,3,3,3,3,
		3,1,5,5,3,3,1,1,3,
		3,1,1,1,1,1,4,1,3,
		3,3,3,3,3,5,1,1,3,
		0,0,0,0,3,1,3,3,3,
		0,0,3,3,3,1,1,3,0,
		0,0,3,2,2,2,1,3,0,
		0,0,3,3,3,3,3,3,0};

Stage03::Stage03(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 9;
	_map_size.h = 9;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage03::~Stage03() {}

