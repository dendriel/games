/*
 * GamePlay.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "GamePlay.h"

#include <iostream>

#include <assert.h>
#include <stdlib.h>

#include "SDL_image.h"

#include "Stage01.h"

using namespace std;


GamePlay::GamePlay()
{
	initResources();
}

GamePlay::~GamePlay()
{
	finalizeResources();
}

void GamePlay::initResources(void)
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		assert(0);
	}


	if( !(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
	{
		cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
		assert(0);
	}

	this->screen = new GameVideo();
	this->screen->init();
}


void GamePlay::finalizeResources(void)
{
	// Free resources.
	free(atlas);
	free(screen);

	// Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

void GamePlay::load(void)
{
	// Save stage reference.
	this->stage = new Stage01(this->screen->renderer());

	this->atlas = new GameAtlas();

	// Fill atlas.
	this->atlas->addSheet(this->stage->sheet());
	this->screen->loadAtlas(this->atlas);

	loadBackground(this->stage, this->backgroud);

	loop();
}

void GamePlay::unload(void)
{
	free(this->atlas);
	this->atlas = NULL;
}

void GamePlay::loadBackground(GameStage *stage, VisualElement *background)
{
	int *map_arr = stage->map_arr();
	SDL_Rect map_size = stage->map_size();
	SDL_Rect map_size_pixel = stage->map_size_pixel();

	SDL_Texture *texture = SDL_CreateTexture(this->screen->renderer(),
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(this->screen->renderer(), texture);

	for (int h = 0; h < map_size.h; h++)
	{
		for (int w = 0; w < map_size.w; w++)
		{
			int tile_id = map_arr[h*map_size.w + w];
			Spritesheet *sheet = this->atlas->getSheet(tile_id);
			GameSprite *sprite = sheet->getSprite(tile_id);

			SDL_Rect destn = {w * sprite->frame.w, w * sprite->frame.y, sprite->frame.w, sprite->frame.h};
			SDL_RenderCopy(this->screen->renderer(), sheet->texture(), &sprite->frame, &destn);
		}
	}

	background = new VisualElement();
	background->setTexture(texture);
	background->setSize(map_size_pixel);

	// Restore default rendering target.
	SDL_SetRenderTarget(this->screen->renderer(), NULL);

	this->screen->addElement(background);
}

void GamePlay::loop(void)
{
	SDL_Event e;

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_UP])
		{
		}
		else if (state[SDL_SCANCODE_DOWN])
		{
		}

		if (state[SDL_SCANCODE_LEFT])
		{
		}
		else if (state[SDL_SCANCODE_RIGHT])
		{
		}

		//User requests quit
		if( e.type == SDL_QUIT )
		{
			return;
		}

		SDL_Delay(1000/60);
		screen->update();
	}
}