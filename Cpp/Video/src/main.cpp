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
	video.push_under_layer(background);


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

	//controller.get_keyDown();
	video.start();

	//Enemy *monster;

	SDLKey key;
	const unsigned char walk_len = 10;
	const unsigned int m_Speed_ms = 100;

	while((key = controller.get_Action()) != SDLK_ESCAPE) {
		switch (key) {
					// UP;
					case SDLK_UP:
						player.add_offset(0, walk_len*-1);
						break;
					// RIGHT
					case SDLK_RIGHT:
						player.add_offset(walk_len, 0);
						break;
					// DOWN:
					case SDLK_DOWN:
						player.add_offset(0, walk_len);
						break;
					// LEFT
					case SDLK_LEFT:
						player.add_offset(walk_len*-1, 0);
						break;
					// STAND
					case SDLK_SPACE:
						video.add_visualElement(new GiantSpider(200, 200));
						usleep(m_Speed_ms*MILI);
						break;
					default:
						cout << "invalid action: " << key << endl;
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
