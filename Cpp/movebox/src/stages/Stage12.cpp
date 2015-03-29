#include "Stage12.h"

#include "Utils.h"

static int Map[] =  {
		3,3,3,3,3,3,0,0,0,
		3,1,1,1,1,3,0,0,0,
		3,1,5,5,5,3,3,0,0,
		3,1,1,3,2,2,3,3,3,
		3,3,1,1,2,2,5,1,3,
		0,3,1,1,4,1,1,1,3,
		0,3,3,3,3,3,3,3,3};

Stage12::Stage12(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 9;
	_map_size.h = 7;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage12::~Stage12() {}

