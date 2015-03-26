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
#include "GamePlay.h"
#include "GameVideo.h"
#include "Spritesheet.h"
#include "GameAtlas.h"
#include "VisualElement.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;



int main(int argc, char *argv[])
{
	GamePlay *game = new GamePlay();

	game->loop();

//	init_resources();
//
//	screen->init();
//	screen->loadAtlas(atlas);
//
//	atlas->addSheet( create_spritesheet(screen->renderer()) );
//
//	//elem->setPos({100, 100});
//	//elem->addSprite("frog_blue_standing_0000.png");
//
//	// Nothing to draw.
//	screen->addElement(elem);
//
//	main_loop(screen, elem);
//
//	free(elem);
//	free(atlas);
//	free(screen);
//
//	screen->finalize();
//	finalize_resources();

	return 0;
}
