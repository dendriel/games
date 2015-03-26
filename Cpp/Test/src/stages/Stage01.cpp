/*
 * Stage01.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#include "Stage01.h"

#include "Utils.h"

Stage01::Stage01(SDL_Renderer *renderer)
{
	SDL_Texture *texture = NULL;

	_texture_name = "images/movebox_256x256.png";

	_sheet = new Spritesheet();

	texture = Utils::loadTexture(_texture_name, renderer);
	_sheet->setTexture(texture);
	_sheet->add("target.png",{0, 0, 63, 63},false,false,{0, 0, 63, 63},{64, 64},{0, 0});
	_sheet->add("box.png",{64, 0, 127, 63},false,false,{64, 0, 127, 63},{64, 64},{0, 0});
	_sheet->add("wall.png",{0, 64, 63, 127},false,false,{0, 64, 63, 127},{64, 64},{0, 0});
	_sheet->add("bug.png",{64, 64, 127, 127},false,false,{64, 64, 127, 127},{64, 64},{0, 0});
}

Stage01::~Stage01()
{
}

