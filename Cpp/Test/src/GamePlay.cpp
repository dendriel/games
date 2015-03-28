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

#include "SDL.h"
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
	this->screen->init("My Label", SCREEN_WIDTH, SCREEN_HEIGHT);
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

	loadMap(this->stage, this->backgroud);

	loadVisualElements();

	loop();
}

void GamePlay::unload(void)
{
	free(this->player);
	this->player = NULL;

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		free(*iter);
	}
	box_list.clear();

	free(this->atlas);
	this->atlas = NULL;

	free(this->stage);
	this->stage = NULL;

	free(this->backgroud);
}

void GamePlay::loadMap(GameStage *stage, VisualElement *background)
{
	int *map_arr = stage->map_arr();
	SDL_Rect map_size = stage->map_size();
	SDL_Rect map_size_pixel = stage->map_size_pixel();

	SDL_Texture *texture = SDL_CreateTexture(this->screen->renderer(),
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			map_size_pixel.w,
			map_size_pixel.h);

	SDL_SetRenderTarget(this->screen->renderer(), texture);

	for (int h = 0; h < map_size.h; h++)
	{
		for (int w = 0; w < map_size.w; w++)
		{
			int pos = h*map_size.w + w;
			int tile_id = map_arr[pos];

			// 0 = empty tile.
			if (tile_id == 0)
			{
				continue;
			}

			// Look for player starting position.
			if (tile_id == stage->player_id())
			{
				this->player = new VisualElement();
				this->player->setPos({w*64, h*64});
				this->player->addSprite(stage->player_sprite());
				// Draw ground in the background instead of the player. The player will be drawn latter.
				tile_id = stage->ground_id();
			}
			// Look for boxes starting position.
			else if (tile_id == stage->box_id())
			{
				VisualElement *box = new VisualElement();
				box->setPos({w*64, h*64});
				box->addSprite(stage->box_sprite());
				this->box_list.push_back(box);
				// Draw ground in the background instead of the box. The box will be drawn latter.
				tile_id = stage->ground_id();
			}
			// Look for targets starting position.
			else if (tile_id == stage->target_id())
			{
				this->target_pos_list.push_back({h, h});
			}

			Spritesheet *sheet = this->atlas->getSheet(tile_id);
			GameSprite *sprite = sheet->getSprite(tile_id);
			SDL_Rect destn = {w * 64, h * 64, 64, 64};

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

void GamePlay::loadVisualElements(void)
{
	this->screen->addElement(this->player);

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		this->screen->addElement(*iter);
	}
}

void GamePlay::loop(void)
{
	SDL_Event e;

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );
		const Uint8 *state = SDL_GetKeyboardState(NULL);



		//User requests quit
		if( e.type == SDL_QUIT )
		{
			return;
		}

		SDL_Delay(1000/60);
		screen->update();
	}
}

/*
if (state[SDL_SCANCODE_UP])
{
	this->player->addPos({0, -64});
}
else if (state[SDL_SCANCODE_DOWN])
{
	this->player->addPos({0, 64});
}

if (state[SDL_SCANCODE_LEFT])
{
	this->player->addPos({-64, 0});
}
else if (state[SDL_SCANCODE_RIGHT])
{
	this->player->addPos({64, 0});
}
 */
