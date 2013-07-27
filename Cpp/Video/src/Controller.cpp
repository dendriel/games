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
	void Controller::get_keyDown(void)
	{
		 SDL_Event event;

		 //while(SDL_PollEvent(&event) == 0); // use this just to get a key.
		 while(SDL_WaitEvent(&event)) {
			 if(event.type == SDL_KEYDOWN) {
				 break;
			 }
		 }
	}

/*************************************************************************************************/
	SDLKey Controller::get_Action(void)
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
