#include "Stage16.h"

#include "Utils.h"

static int Map[] =  {
		3,3,3,3,3,3,3,3,0,
		3,1,1,1,1,1,1,3,0,
		3,1,3,5,5,1,1,3,0,
		3,1,2,2,2,3,1,3,0,
		3,3,2,2,2,5,1,3,3,
		0,3,1,3,3,1,5,1,3,
		0,3,5,1,1,5,1,1,3,
		0,3,1,1,3,1,1,4,3,
		0,3,3,3,3,3,3,3,3};

Stage16::Stage16(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 9;
	_map_size.h = 9;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage16::~Stage16() {}

