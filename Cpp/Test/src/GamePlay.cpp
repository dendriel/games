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




// TODO: remove this.
//Spritesheet *GamePlay::createSpritesheet(SDL_Renderer *renderer)
//{
//	Spritesheet *sheet = new Spritesheet();
//	SDL_Texture *texture = loadTexture("images/leaping_frog_atlas.png", renderer);
//
//	// Load sheet image file.
//	sheet->setTexture(texture);
//
//	// Register sprites.
//	sheet->add("button_play.png",
//			{191, 2, 259, 114},
//			false,
//			true,
//			{3, 3, 59, 114},
//			{265, 120},
//			{0.5, 0.5});
//
//	sheet->add("frog_blue_leaping_0000.png",
//		{2,193,48,32},
//		false,
//		false,
//		{0,0,48,32},
//		{48,32},
//		{0.5,0.5});
//
//	sheet->add("frog_blue_leaping_0001.png",
//		{303,118,50,41},
//		true,
//		false,
//		{0,0,50,41},
//		{50,41},
//		{0.5,0.5});
//
//	sheet->add("frog_blue_leaping_0002.png",
//		{251,118,50,57},
//		false,
//		false,
//		{0,0,50,57},
//		{50,57},
//		{0.5,0.5});
//
//	sheet->add("frog_blue_leaping_0003.png",
//		{329,170,50,41},
//		true,
//		false,
//		{0,0,50,41},
//		{50,41},
//		{0.5,0.5});
//
//
//		sheet->add("frog_blue_standing_0000.png",
//		{52,193,48,32},
//		false,
//		false,
//		{0,0,48,32},
//		{48,32},
//		{0.5,0.5});
//
//		sheet->add("frog_blue_standing_0001.png",
//		{102,193,48,32},
//		false,
//		false,
//		{0,0,48,32},
//		{48,32},
//		{0.5,0.5});
//
//		sheet->add("frog_blue_standing_0002.png",
//		{152,193,48,32},
//		false,
//		false,
//		{0,0,48,32},
//		{48,32},
//		{0.5,0.5});
//
//	//sheet->dump();
//
//	/*
//	std::string filename;
//	SDL_Rect frame;
//	bool rotated;
//	bool trimmed;
//	SDL_Rect sprite_source_size;
//	SDL_Rect source_size;
//	SDL_Rect pivot;
//	*/
//
//	return sheet;
//}

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
}

void GamePlay::unload(void)
{
	free(this->atlas);
	this->atlas = NULL;
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
//		//User presses a key
//		else if( e.type == SDL_KEYDOWN )
//		{
//			//Select surfaces based on key press
//			switch( e.key.keysym.sym )
//			{
//				case SDLK_UP:
//					cout << "up" << endl;
//					elem->setPos({elem->pos().x, elem->pos().y - 1});
//				break;
//
//				case SDLK_DOWN:
//					cout << "down" << endl;
//					elem->setPos({elem->pos().x, elem->pos().y + 1});
//				break;
//
//				default:
//				break;
//			}
//			switch( e.key.keysym.sym )
//			{
//				case SDLK_LEFT:
//					cout << "left" << endl;
//					elem->setPos({elem->pos().x - 1, elem->pos().y});
//				break;
//
//				case SDLK_RIGHT:
//					cout << "right" << endl;
//					elem->setPos({elem->pos().x + 1, elem->pos().y});
//				break;
//
//				default:
//				break;
//			}
//		}

		SDL_Delay(1000/60);
		screen->update();
	}
}
