/*
 * GameVideo.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: vitor
 */

#include "GameVideo.h"

#include <iostream>
#include <assert.h>

using namespace std;

GameVideo::GameVideo():
window(NULL),
_renderer(NULL),
atlas(NULL)
{
	// TODO Auto-generated constructor stub

}

GameVideo::~GameVideo()
{
	// TODO Auto-generated destructor stub
}

void GameVideo::init(string label, unsigned int width, unsigned int height)
{
	if (window != NULL)
	{
		cout << "Display already initialized." << endl;
		return;
	}

	// Create window.
	window = SDL_CreateWindow(label.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if( window == NULL )
	{
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		assert(0);
	}

	// Create rendered.
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if (_renderer == NULL)
	{
		cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
		assert(0);
	}

	if (SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff) != 0)
	{
		cout << "Failed to set renderer draw color." << endl;
	}
}

void GameVideo::finalize(void)
{
	SDL_DestroyRenderer(_renderer);

	SDL_DestroyWindow(window);
}

void GameVideo::update(void)
{
	if (atlas == NULL)
	{
		cout << "No atlas was loaded into game video." << endl;
		assert(0);
	}

	SDL_RenderClear(_renderer);

	for (vector<VisualElement *>::iterator iter = element_list.begin(); iter != element_list.end(); ++iter)
	{
		VisualElement *element = *iter;
		SDL_Texture *texture = NULL;
		Spritesheet *sheet = NULL;
		GameSprite *sprite = NULL;
		SDL_Rect *source = NULL;
		SDL_Rect destn;

		if (element->texture() != NULL)
		{
			texture = element->texture();
			source = NULL;
			destn = {element->pos().x, element->pos().y, element->size().w, element->size().h};
		}
		else
		{
			sheet = atlas->getSheet(element->curr_sprite());
			if (sheet == NULL)
			{
				cout << "The sheet for the sprite \"" << element->curr_sprite() << "\" wasn't found in the atlas." << endl;
				assert(0);
			}

			sprite = sheet->getSprite(element->curr_sprite());

			texture = sheet->texture();
			destn = {element->pos().x, element->pos().y, sprite->frame.w, sprite->frame.h};
			source = &sprite->frame;
		}

		if (element->rotated() == true)
		{
			SDL_RenderCopyEx(_renderer, texture, source, &destn, element->rotation_angle_degrees(), NULL, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopy(_renderer, texture, source, &destn);
		}
	}

	//Update screen
	SDL_RenderPresent(_renderer);
}
