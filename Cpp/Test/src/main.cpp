/*
 * main.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: vitor.rozsa
 */

// C++ basic libs.
#include <iostream>

// C basic libs.
#include <assert.h>

// Thirdy part libs.
#include "SDL.h"
#include "SDL_image.h"

// Internal libs.
#include "GameVideo.h"
#include "Spritesheet.h"
#include "GameAtlas.h"
#include "VisualElement.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

void init_resources(void)
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
}

void finalize_resources(void)
{
	// Quit SDL subsystems.
	IMG_Quit();

	SDL_Quit();
}


SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture *texture = NULL;

	//Load image at specified path
	SDL_Surface *surface = IMG_Load(path.c_str());
	if( surface == NULL )
	{
		cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
		assert(0);
	}


	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == NULL)
	{
		cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError();
		assert(0);
	}

	// Get rid of old loaded surface
	SDL_FreeSurface(surface);

	return texture;
}

Spritesheet *create_spritesheet(SDL_Renderer *renderer)
{
	Spritesheet *sheet = new Spritesheet();
	SDL_Texture *texture = loadTexture("images/leaping_frog_atlas.png", renderer);

	// Load sheet image file.
	sheet->setTexture(texture);

	// Register sprites.
	sheet->add("button_play.png",
			{191, 2, 259, 114},
			false,
			true,
			{3, 3, 59, 114},
			{265, 120},
			{0.5, 0.5});

	sheet->add("frog_blue_leaping_0000.png",
		{2,193,48,32},
		false,
		false,
		{0,0,48,32},
		{48,32},
		{0.5,0.5});

	sheet->add("frog_blue_leaping_0001.png",
		{303,118,50,41},
		true,
		false,
		{0,0,50,41},
		{50,41},
		{0.5,0.5});

	sheet->add("frog_blue_leaping_0002.png",
		{251,118,50,57},
		false,
		false,
		{0,0,50,57},
		{50,57},
		{0.5,0.5});

	sheet->add("frog_blue_leaping_0003.png",
		{329,170,50,41},
		true,
		false,
		{0,0,50,41},
		{50,41},
		{0.5,0.5});


		sheet->add("frog_blue_standing_0000.png",
		{52,193,48,32},
		false,
		false,
		{0,0,48,32},
		{48,32},
		{0.5,0.5});

		sheet->add("frog_blue_standing_0001.png",
		{102,193,48,32},
		false,
		false,
		{0,0,48,32},
		{48,32},
		{0.5,0.5});

		sheet->add("frog_blue_standing_0002.png",
		{152,193,48,32},
		false,
		false,
		{0,0,48,32},
		{48,32},
		{0.5,0.5});

	//sheet->dump();

	/*
	std::string filename;
	SDL_Rect frame;
	bool rotated;
	bool trimmed;
	SDL_Rect sprite_source_size;
	SDL_Rect source_size;
	SDL_Rect pivot;
	*/

	return sheet;
}

void main_loop(GameVideo *screen, VisualElement *elem)
{
	SDL_Event e;

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_UP])
		{
			elem->setPos({elem->pos().x, elem->pos().y - 1});

		}
		else if (state[SDL_SCANCODE_DOWN])
		{
			elem->setPos({elem->pos().x, elem->pos().y + 1});

		}

		if (state[SDL_SCANCODE_LEFT])
		{
			elem->setPos({elem->pos().x - 1, elem->pos().y});

		}
		else if (state[SDL_SCANCODE_RIGHT])
		{
			elem->setPos({elem->pos().x + 1, elem->pos().y});

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

int main(int argc, char *argv[])
{
	GameVideo *screen = new GameVideo();
	GameAtlas *atlas = new GameAtlas();
	VisualElement *elem = new VisualElement();

	init_resources();

	screen->init();
	screen->loadAtlas(atlas);

	atlas->addSheet( create_spritesheet(screen->renderer()) );

	elem->setPos({100, 100});
	elem->addSprite("frog_blue_standing_0000.png");

	// Nothing to draw.
	screen->addElement(elem);

	main_loop(screen, elem);

	free(elem);
	free(atlas);
	free(screen);

	screen->finalize();
	finalize_resources();

	return 0;
}
