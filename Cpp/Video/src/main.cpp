#include <iostream>
#include <unistd.h>
#include "SDL/SDL.h"

#include "Video.h"
#include "VisualElement.h"
#include "Controller.h"
#include "GiantSpider.h"

using namespace std;


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

	Video video;
	Controller controller;

	const char *path = "image/grassland_640x480.bmp";
	SDL_Surface *background;
	background = SDL_LoadBMP(path);
	if (background == NULL) {
		cout << "Failed to initialize background! Image path: \"" << path << "\"" << endl;
	}
	//video.push_under_layer(background);
	SDL_Surface *map = NULL;
	SDL_Rect map_size;

	map_size.w = VIDEO_SCREEN_WIDTH;
	map_size.h = VIDEO_SCREEN_HEIGHT;

	cout << "will load the map" << endl;
	if (build_mapview(&map, map_size) == 0) {
		video.push_under_layer(map);
	}

	SDL_Surface *pView;
	pView = SDL_LoadBMP("image/critter.bmp");
	if (pView == NULL) {
		cout << "Failed to initialize Enemy! Image path: \"" << path << "\"" << endl;
	}
	VisualElement player;
	player.set_viewpoint(pView, 0);


	GiantSpider crit(200, 200);
	video.add_visualElement(&crit);
	video.add_visualElement(&player);

	video.start();

	en_ctrl_actions action;
	const unsigned char walk_len = 10;
	const unsigned int m_Speed_ms = 100;

	while((action = controller.get_action()) != CTRL_EXIT) {
		switch (action) {
					// UP;
					case CTRL_MOVE_UP:
						player.add_offset(0, walk_len*-1);
						break;
					// RIGHT
					case CTRL_MOVE_RIGHT:
						player.add_offset(walk_len, 0);
						break;
					// DOWN:
					case CTRL_MOVE_DOWN:
						player.add_offset(0, walk_len);
						break;
					// LEFT
					case CTRL_MOVE_LEFT:
						player.add_offset(walk_len*-1, 0);
						break;
					case CTRL_NONE:
						/* Nothing to do. */
						break;
					// STAND
					case CTRL_SUMMON:
						video.add_visualElement(new GiantSpider(200, 200));
						usleep(m_Speed_ms*MILI);
						break;
					default:
						cout << "invalid action: " << action << endl;
						break;
					}
		usleep(m_Speed_ms*MILI);
	}

	controller.get_keyDown();
	video.freeze();
	controller.get_keyDown();

	SDL_FreeSurface(background);

	SDL_Quit();

	return 0;
}
