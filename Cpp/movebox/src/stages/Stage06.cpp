#include "Stage06.h"

#include "Utils.h"

static int Map[] =  {
		0,0,0,3,3,3,3,3,3,3,
		0,0,3,3,1,1,3,1,4,3,
		0,0,3,1,1,1,3,5,1,3,
		0,0,3,5,1,1,5,1,1,3,
		0,0,3,1,5,3,3,1,1,3,
		3,3,3,1,5,1,3,1,3,3,
		3,2,2,2,2,2,1,1,3,0,
		3,3,3,3,3,3,3,3,3,0};

Stage06::Stage06(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 10;
	_map_size.h = 8;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage06::~Stage06() {}

