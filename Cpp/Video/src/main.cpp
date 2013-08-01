#include <iostream>
#include <unistd.h>
#include "SDL/SDL.h"

#include "Video.h"
#include "VisualElement.h"
#include "Controller.h"
#include "Scenery.h"
#include "GiantSpider.h"

using namespace std;


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

	Video video;
	// Character player_character; //TODO
	Scenery scen(video);
	scen.play();

	/*
	Engine engine;
	engine.start();
	 */

	SDL_Quit();

	return 0;
}
