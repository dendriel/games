/*
 * StageDefault.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#include "StageDefault.h"

#include "Utils.h"

StageDefault::StageDefault(SDL_Renderer *renderer)
{
	/**
	 * For the created stages, i won't parse the text files data. It's is possible to get it from
	 * json files, but we would need a parser for this.
	 */

	_sheet = new Spritesheet("images/movebox_128x192.png", renderer);
	_sheet->add("tile.png",{0, 0, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 1);
	_sheet->add("target.png",{64, 0, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 2);
	_sheet->add("wall.png",{0, 64, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 3);
	_sheet->add("bug.png",{64, 64, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 4);
	_sheet->add("box.png",{0, 128, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 5);
	_sheet->add("box_done.png",{64, 128, 64, 64},false,false,{0, 0, 0, 0},{64, 64},{0, 0}, 6);

	_ground_id = 1;
	_target_id = 2;
	_player_id = 4;
	_box_id    = 5;
	_box_done_id = 6;

	_player_sprite = "bug.png";
	_target_sprite = "target.png";
	_box_sprite = "box.png";
	_box_done_sprite = "box_done.png";
}

StageDefault::~StageDefault()
{
	delete(_sheet);
	_sheet = NULL;
}

