#include "Stage15.h"

#include "Utils.h"

static int Map[] =  {
		3,3,3,3,3,3,3,
		3,2,2,5,2,2,3,
		3,2,2,3,2,2,3,
		3,1,5,5,5,1,3,
		3,1,1,5,1,1,3,
		3,1,5,5,5,1,3,
		3,1,1,3,4,1,3,
		3,3,3,3,3,3,3};

Stage15::Stage15(SDL_Renderer *renderer):
StageDefault(renderer)
{
	_map_arr = Map;
	_map_size.w = 7;
	_map_size.h = 8;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};
}

Stage15::~Stage15() {}

