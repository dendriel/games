/*
 * VisualElement.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "GameSprite.h"

GameSprite::GameSprite(std::string filename,
		SDL_Rect frame,
		bool rotated,
		bool trimmed,
		SDL_Rect sprite_source_size,
		SDL_Rect source_size,
		SDL_Rect pivot,
		unsigned int id):
filename(filename),
frame(frame),
rotated(rotated),
trimmed(trimmed),
sprite_source_size(sprite_source_size),
source_size(source_size),
pivot(pivot),
id(id)
{
	// TODO Auto-generated constructor stub

}

GameSprite::~GameSprite() {
	// TODO Auto-generated destructor stub
}

