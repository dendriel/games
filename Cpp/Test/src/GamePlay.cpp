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

			map_state.push_back(tile_id);

			// 0 = empty tile.
			if (tile_id == 0)
			{
				continue;
			}

			// Look for player starting position.
			if (tile_id == stage->player_id())
			{
				// If this position is the player position, change the internal map state to ground.
				map_state[map_state.size() - 1] = stage->ground_id();

				this->player = new VisualElement();
				this->player->setPos({w*64, h*64});
				this->player->addSprite(stage->player_sprite());
				// Draw ground in the background instead of the player. The player will be drawn latter.
				tile_id = map_state[map_state.size() - 1];
			}
			// Look for boxes starting position.
			else if (tile_id == stage->box_id())
			{
				VisualElement *box = new VisualElement();
				box->setPos({w*64, h*64});
				box->addSprite(stage->box_done_sprite());
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
	/**
	 * We want to allow the player to move one square per key press/release. So we will keep track
	 * of the key status here. Can move only if the key was released.
	 */
	bool can_move = true;

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );

		//User requests quit
		if( e.type == SDL_QUIT )
		{
			cout << "Quit game!" << endl;
			return;
		}
		//User presses a key
		else if ( (e.type == SDL_KEYDOWN) && can_move)
		{
			movePlayer(e.key.keysym.sym);
			can_move = false;
		}
		else if ( e.type == SDL_KEYUP)
		{
			can_move = true;
		}

		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_KEYUP);

		SDL_Delay(1000/60);
		screen->update();
	}
}

void GamePlay::movePlayer(SDL_Keycode dir)
{
	SDL_Point orientation;

	switch(dir)
	{
		case SDLK_UP:
			orientation = {0, -1};
			break;

		case SDLK_DOWN:
			orientation = {0, 1};
			break;

		case SDLK_LEFT:
			orientation = {-1, 0};
			break;

		case SDLK_RIGHT:
			orientation = {1, 0};
			break;

		default:
			return;
	}

	checkCanMove(&orientation);

}

// I don't like very much passing pointer to such small variable, but.. looks like we will save some
// memory.
void GamePlay::checkCanMove(SDL_Point *orientation)
{
	SDL_Point origin = {player->posX() / 64, player->posY() / 64};
	SDL_Rect map_size = stage->map_size();

	SDL_Point destn;

	// Set target position in the matrix.
	destn = {origin.x + orientation->x, origin.y + orientation->y};

	// Translate matrix position to array position.
	int pos = destn.y*map_size.w + destn.x;
	int tile_id = map_state[pos];

	cout << pos << " - move to tile id: " << tile_id  << endl;

	// Move box.
	if ( (tile_id == stage->box_id()) || (tile_id == stage->box_done_id()) )
	{
		SDL_Point destn_after = {origin.x + orientation->x*2, origin.y + orientation->y*2};
		int pos_after =  destn_after.y*map_size.w + destn_after.x;
		int tile_id_after = map_state[pos_after];

		if ( (tile_id_after != stage->ground_id()) &&
				(tile_id_after != stage->target_id()) )
		{
			// The box can,'t move if the next tile isn't ground or target.
			return;
		}

		VisualElement *box = getBoxAt(&destn);
		box->setPos({destn_after.x * 64, destn_after.y * 64});

		// Next position is a target.
		if (map_state[pos_after] == stage->target_id())
		{
			map_state[pos_after] = stage->box_done_id();
			box->setSprite(stage->box_done_sprite());
		}
		else
		{
			map_state[pos_after] = stage->box_id();
			// TODO: we will need to keep track of the box over/off target so we can check for victory.
			box->setSprite(stage->box_sprite());
		}

		// Free the position.
		if (map_state[pos] == stage->box_done_id())
		{
			map_state[pos] = stage->target_id();
		}
		else
		{
			map_state[pos] = stage->ground_id();
		}

		// Check if destn is a target!!

		// Move the player.
		player->setPos({destn.x * 64, destn.y * 64});
		return;
	}



	if ( (tile_id == stage->ground_id()) || (tile_id == stage->target_id()) )
	{
		player->addPos({orientation->x*64, orientation->y*64});
		return;
	}
}

VisualElement *GamePlay::getBoxAt(SDL_Point *pos)
{
	SDL_Point pos_pixels = {pos->x * 64, pos->y *64};

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		VisualElement *box = *iter;

		if ( (box->posX() == pos_pixels.x) && (box->posY() == pos_pixels.y) )
		{
			return box;
		}
	}

	cout << "The box at position " << pos_pixels.x << "," << pos_pixels.y << " was not found!" << endl;
	assert(0);
	return NULL;
}

/*

// SDL_PumpEvents() to filter events. Maybe useful in the code bellow.

const Uint8 *state = SDL_GetKeyboardState(NULL);

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
