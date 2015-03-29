#include "Stage05.h"

#include "Utils.h"

static int Map[] =  {
		0,3,3,3,3,0,0,0,
		0,3,1,4,3,3,3,0,
		0,3,1,5,1,1,3,0,
		3,3,3,1,3,1,3,3,
		3,2,3,1,3,1,1,3,
		3,2,5,1,1,3,1,3,
		3,2,1,1,1,5,1,3,
		3,3,3,3,3,3,3,3};

Stage05::Stage05(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 8;
	_map_size.h = 8;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage05::~Stage05() {}

