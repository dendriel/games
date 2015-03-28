/*
 * Stage01.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#include "Stage01.h"

#include "Utils.h"


static int Map[] =  {0, 0, 3, 3, 3, 3, 3,
					 3, 3, 3, 1, 2, 1, 3,
					 3, 1, 1, 4, 5, 2, 3,
					 3, 1, 5, 3, 1, 1, 3,
					 3, 1, 1, 3, 3, 3, 3,
					 3, 3, 3, 3, 0, 0, 0};


//static int Map[] = {1, 1, 1, 1, 1,
//					 1, 1, 1, 1, 1,
//					 1, 1, 1, 1, 1,
//					 1, 1, 1, 1, 1,
//					 1, 1, 1, 1, 1,
//					 1, 1, 1, 1, 1};


Stage01::Stage01(SDL_Renderer *renderer)
{
	SDL_Texture *texture = NULL;

	_texture_name = "images/movebox_128x192.png";

	_sheet = new Spritesheet();

	texture = Utils::loadTexture(_texture_name, renderer);
	_sheet->setTexture(texture);
	_sheet->add("tile.png",{0, 0, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 1);
	_sheet->add("target.png",{64, 0, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 2);
	_sheet->add("wall.png",{0, 64, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 3);
	_sheet->add("bug.png",{64, 64, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 4);
	_sheet->add("box.png",{0, 128, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 5);

	_map_arr = Map;
	_map_size.w = 7;
	_map_size.h = 6;
	_map_size_pixel = {0, 0, _map_size.w * 64, _map_size.h * 64};

	_ground_id = 1;
	_target_id = 2;
	_player_id = 4;
	_box_id = 5;

	_player_sprite = "bug.png";
	_target_sprite = "target.png";
	_box_sprite = "box.png";

}

Stage01::~Stage01()
{
}

