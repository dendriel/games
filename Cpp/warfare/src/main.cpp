#include <iostream>
#include <unistd.h>
#include "SDL/SDL.h"

#include "Video.h"
#include "GameBoard.h"
//#include "VisualElement.h"
//#include "Controller.h"
//#include "Scenery.h"
//#include "GiantSpider.h"

using namespace std;


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

	Video video;
	GameBoard board(video, 5, 5);

	board.draw();

	SDL_Quit();

	return 0;
}
