/*
 * Controller.cpp
 *
 *  Created on: 20/07/2013
 *      Author: vitor
 */

#include "Controller.h"

/*************************************************************************************************/
	Controller::Controller(void)
	{
		(void) SDL_EnableUNICODE(1);
		cout << "Controller initialized." << endl;
	}

/*************************************************************************************************/
	en_ctrl_actions Controller::get_action(void)
	{
		Uint8 *keystate = NULL;

		SDL_PumpEvents();
		keystate = SDL_GetKeyState(NULL);

		if (keystate[SDLK_UP]) {
			return CTRL_MOVE_UP;
		}

		if (keystate[SDLK_RIGHT]) {
			return CTRL_MOVE_RIGHT;
		}

		if (keystate[SDLK_LEFT]) {
			return CTRL_MOVE_LEFT;
		}

		if (keystate[SDLK_DOWN]) {
			return CTRL_MOVE_DOWN;
		}

		if (keystate[SDLK_ESCAPE]) {
			return CTRL_EXIT;
		}

		if (keystate[SDLK_SPACE]) {
			return CTRL_SUMMON;
		}

		return CTRL_NONE;
	}

/*************************************************************************************************/
	SDLKey Controller::get_keyDown(void)
	{
		SDL_Event event;

		//while(SDL_PollEvent(&event) == 0); // use this just to get a key.
		while(SDL_WaitEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
				break;
			}
		}

		return event.key.keysym.sym;
	}

/*************************************************************************************************/
/*								Private Functions.												 */
/*************************************************************************************************/
