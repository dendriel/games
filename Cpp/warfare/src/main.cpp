#include <iostream>
#include <unistd.h>
#include "SDL/SDL.h"

#include "Video.h"
#include "Viewpoints.h"
#include "GameBoard.h"
#include "Controller.h"
//#include "Controller.h"
//#include "Scenery.h"
//#include "GiantSpider.h"

using namespace std;

#define GAME_VIDEO_WIDTH 800
#define GAME_VIDEO_HEIGHT 600
#define GAME_TITLE "Warfare"

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

	Controller control;
	Video video(GAME_VIDEO_WIDTH, GAME_VIDEO_HEIGHT, GAME_TITLE);
	Video video_virtual2(VIDEO_VIRTUAL_SCREEN, &video, 450, 450);
	Video video_virtual(VIDEO_VIRTUAL_SCREEN, &video, 350, 350);
	video.start();

	GameBoard board(video_virtual, 5, 5);
	board.draw();


	control.get_keyDown();

	SDL_Surface *map1 = NULL, *map2 = NULL;
	Viewpoints::load_surface("resources/misc/2d_medieval.bmp", &map1);
	Viewpoints::load_surface("resources/sprites/warrior.bmp", &map2);

	video_virtual2.push_under_layer(map1);
	video_virtual2.push_under_layer(map2);

	video_virtual2.start();


	control.get_keyDown();

	SDL_Quit();

	return 0;
}
