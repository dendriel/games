#include "Stage08.h"

#include "Utils.h"

static int Map[] =  {
		0,0,3,3,3,3,3,3,
		0,0,3,1,1,1,1,3,
		3,3,3,5,5,5,1,3,
		3,4,1,5,2,2,1,3,
		3,1,5,2,2,2,3,3,
		3,3,3,3,1,1,3,0,
		0,0,0,3,3,3,3,0};

Stage08::Stage08(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 8;
	_map_size.h = 7;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage08::~Stage08() {}

