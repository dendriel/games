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
	Controller controller;
	Scenery scen(video);

	SDL_Surface *pView;
	pView = SDL_LoadBMP("image/critter.bmp");
	if (pView == NULL) {
		cout << "Failed to initialize player view!"<< endl;
	}
	VisualElement player;
	player.set_viewpoint(pView, 0);

	video.add_visualElement(&player);


	GiantSpider crit(200, 200);
	video.add_visualElement(&crit);

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

	SDL_Quit();

	return 0;
}
