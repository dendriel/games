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

#include "default_stages.h"

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

	box_on_target = 0;
	num_of_target = 0;

	// Fill stage list.
	stage_list.push_back(new Stage03(screen->renderer()));
	stage_list.push_back(new Stage02(screen->renderer()));
	stage_list.push_back(new Stage01(screen->renderer()));
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

void GamePlay::loadStage()
{
	atlas = new GameAtlas();

	// Fill atlas.
	atlas->addSheet(stage->sheet());
	screen->loadAtlas(atlas);

	background = new VisualElement();

	loadMap();
}

void GamePlay::unloadStage(void)
{
	// Clear screen.
	screen->removeAllElements();
	screen->loadAtlas(NULL);

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		delete(*iter);
	}
	box_list.clear();

	delete(player);
	player = NULL;

	delete(background);
	background = NULL;

	delete(atlas);
	atlas = NULL;

	num_of_target = 0;
	box_on_target = 0;

	// Clear current id map.
	map_state.clear();
}

void GamePlay::loadMap()
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
				cout << "Player pos: " << w*64 << "," << h*64 << endl;
			}
			// Look for boxes starting position.
			else if ( (tile_id == stage->box_id()) || (tile_id == stage->box_done_id()) )
			{
				VisualElement *box = new VisualElement();
				box->setPos({w*64, h*64});
				box->addSprite(stage->box_done_sprite());
				box->addSprite(stage->box_sprite());
				this->box_list.push_back(box);

				// If box is over a target.
				if (tile_id == stage->box_done_id())
				{
					box->setSprite(stage->box_done_sprite());
					num_of_target++;
					box_on_target++;
				}

				// Draw ground in the background instead of the box. The box will be drawn latter.
				tile_id = stage->ground_id();
			}
			// Look for targets starting position.
			else if (tile_id == stage->target_id())
			{
				num_of_target++;
			}

			Spritesheet *sheet = this->atlas->getSheet(tile_id);
			GameSprite *sprite = sheet->getSprite(tile_id);
			SDL_Rect destn = {w * 64, h * 64, 64, 64};

			SDL_RenderCopy(this->screen->renderer(), sheet->texture(), &sprite->frame, &destn);
		}
	}

	background->setTexture(texture);
	background->setSize(map_size_pixel);

	// Restore default rendering target.
	SDL_SetRenderTarget(this->screen->renderer(), NULL);

	// Load moveable Elements.
	loadVisualElements();

	// Can't start a level that is already finished.
	cout << "status: " << box_on_target << "/" << num_of_target << endl;
	assert(box_on_target < num_of_target);
}

void GamePlay::loadVisualElements(void)
{
	screen->addElement(background);
	screen->addElement(player);

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		screen->addElement(*iter);
	}
}

void GamePlay::mainLoop(void)
{
	int state;

	// Stage list must have at least one stage.
	assert(stage_list.size() > 0);

	stage = stage_list[stage_list.size() - 1];
	stage_list.pop_back();

	do
	{
		// Load stage data.
		loadStage();

		// Play stage.
		state = stageLoop();

		// Restart level.
		if (state == 1)
		{
			// Unload stage data.
			unloadStage();
			// Continue with the same stage from beginning.
			continue;
		}
		// Quit game.
		else if (state == 2)
		{
			return;
		}

		// Unload stage data.
		unloadStage();


		// Remove stage.
		delete(stage);
		stage = NULL;

		// Pop a new stage.
		stage = stage_list[stage_list.size() - 1];
		stage_list.pop_back();

	} while (stage_list.size() > 0);

}

/**
 * Return codes.
 * 0 = stage cleared.
 * 1 = replay stage.
 * 2 = Player exited the game.
 */
int GamePlay::stageLoop(void)
{
	SDL_Event e;

	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_KEYUP);

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
			return 2;
		}
		//User presses a key
		else if ( (e.type == SDL_KEYDOWN) && can_move)
		{
			// Restart stage.
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				return 1;
			}
			// Move player.
			else
			{
				movePlayer(e.key.keysym.sym);
				can_move = false;
			}
		}
		else if ( e.type == SDL_KEYUP)
		{
			can_move = true;
		}

		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_KEYUP);
		screen->update();

		if (levelFinished() == true)
		{
			cout << "Victory!" << endl;
			return 0;
		}

		SDL_Delay(1000/60);
	}

	return 0;
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

	checkMove(&orientation);
}

// I don't like very much passing pointer to such small variable, but.. looks like we will save some
// memory.
void GamePlay::checkMove(SDL_Point *orientation)
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
			box_on_target++;
		}
		else
		{
			map_state[pos_after] = stage->box_id();
			box->setSprite(stage->box_sprite());
		}

		// Free the position.
		if (map_state[pos] == stage->box_done_id())
		{
			map_state[pos] = stage->target_id();
			box_on_target--;
		}
		else
		{
			map_state[pos] = stage->ground_id();
		}

		// Move the player.
		player->setPos({destn.x * 64, destn.y * 64});
	}
	else if ( (tile_id == stage->ground_id()) || (tile_id == stage->target_id()) )
	{
		player->addPos({orientation->x*64, orientation->y*64});
	}

	cout << "status: " << box_on_target << "/" << num_of_target << endl;

	return;
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
