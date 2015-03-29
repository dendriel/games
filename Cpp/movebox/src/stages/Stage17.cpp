#include "Stage17.h"

#include "Utils.h"

static int Map[] =  {
		0,0,3,3,3,3,3,0,0,0,
		3,3,3,1,1,1,3,3,3,3,
		3,1,1,1,5,1,5,1,1,3,
		3,1,5,1,1,1,5,1,4,3,
		3,3,3,5,5,3,3,3,3,3,
		0,0,3,1,1,2,2,3,0,0,
		0,0,3,2,2,2,2,3,0,0,
		0,0,3,3,3,3,3,3,0,0};

Stage17::Stage17(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 10;
	_map_size.h = 8;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage17::~Stage17() {}

