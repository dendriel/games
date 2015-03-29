/*
 * Spritesheet.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "Spritesheet.h"

#include <iostream>

#include "Utils.h"

using namespace std;

Spritesheet::Spritesheet(std::string texture_name, SDL_Renderer *renderer):
_texture(NULL)
{
	if ( (texture_name.size() > 0) && (renderer != NULL) )
	{
		setTexture(texture_name, renderer);
	}
}

Spritesheet::~Spritesheet()
{
	for(map<string, GameSprite *>::iterator iter=sprite_list.begin(); iter != sprite_list.end(); iter++)
	{
		delete(iter->second);
	}

	sprite_list.clear();

	SDL_DestroyTexture(_texture);
	_texture = NULL;
}

void Spritesheet::add(std::string filename,
		SDL_Rect frame,
		bool rotated,
		bool trimmed,
		SDL_Rect sprite_source_size,
		SDL_Rect source_size,
		SDL_Rect pivot,
		unsigned int id)
{
	GameSprite *sprite = new GameSprite(filename, frame, rotated, trimmed, sprite_source_size,
										source_size, pivot, id);

	// Should check before adding a new sprite to make sure not override any entry.
	sprite_list[filename] = sprite;
}


GameSprite *Spritesheet::getSprite(const string name)
{
	for(map<string, GameSprite *>::iterator iter=sprite_list.begin(); iter != sprite_list.end(); iter++)
	{
		GameSprite *sprite = iter->second;

		if (sprite->filename.compare(name) == 0)
		{
			return sprite;
		}
	}

	return NULL;
}


GameSprite *Spritesheet::getSprite(const unsigned int id)
{
	for(map<string, GameSprite *>::iterator iter=sprite_list.begin(); iter != sprite_list.end(); iter++)
	{
		GameSprite *sprite = iter->second;

		if (sprite->id == id)
		{
			return sprite;
		}
	}

	return NULL;

}

void Spritesheet::setTexture(string texture_name, SDL_Renderer *renderer)
{
	_texture = Utils::loadTexture(texture_name, renderer);
}

SDL_Texture *Spritesheet::texture(void)
{
	return _texture;
}


void Spritesheet::dump(void)
{
	for(map<string, GameSprite *>::iterator iter=sprite_list.begin(); iter != sprite_list.end(); iter++)
	{
		GameSprite *sprite = iter->second;
		cout << "\"" << iter->first << "\"" << endl;
		cout << "          filename: \"" << sprite->filename << "\"" << endl;
		cout << "             frame: {" << sprite->frame.x << ", " << sprite->frame.y << ", " <<sprite->frame.w << ", " << sprite->frame.h << "}" << endl;
		cout << "           rotated: " << sprite->rotated << endl;
		cout << "           trimmed: " << sprite->trimmed << endl;
		cout << "sprite_source_size: {" << sprite->sprite_source_size.x << ", " << sprite->sprite_source_size.y << ", " <<sprite->sprite_source_size.w << ", " << sprite->sprite_source_size.h << "}" << endl;
		cout << "       source_size: {" << sprite->source_size.x << ", " << sprite->source_size.y << ", " <<sprite->source_size.w << ", " << sprite->source_size.h << "}" << endl;
		cout << "             pivot: {" << sprite->pivot.x << ", " << sprite->pivot.y << ", " <<sprite->pivot.w << ", " << sprite->pivot.h << "}" << endl << endl;
	}
}
