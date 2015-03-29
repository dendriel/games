#include "Stage09.h"

#include "Utils.h"

static int Map[] =  {
		0,0,3,3,3,3,3,0,
		3,3,3,1,1,4,3,0,
		3,1,1,5,2,1,3,3,
		3,1,1,2,5,2,1,3,
		3,3,3,1,6,5,1,3,
		0,0,3,1,1,1,3,3,
		0,0,3,3,3,3,3,0};

Stage09::Stage09(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 8;
	_map_size.h = 7;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage09::~Stage09() {}

