#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <tr1/cstdint>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "Video.h"
#include "VirtualVideo.h"
#include "Viewpoints.h"
#include "GameBoard.h"
#include "Controller.h"

#include "game_defines.h"
#include "sprites_defines.h"
#include "debug.h"

using namespace std;


class Main {
private:
/* Resources. */
	Controller *m_Control;		//!< Game controller interface.
	Video *m_RealScreen;		//!< Video object to represent the hard screen.
	VirtualVideo *m_VirtualScreen_board;	//!< Video object to represent the game board.
	VirtualVideo *m_VirtualScreen_menu;	//!< Video object to represent the game menu.
	VirtualVideo *m_VirtualScreen_chatbar;	//!< Video object to represent the game chatbar.

	GameBoard *m_GameBoard;		//!< Game-play board.

/* Methods. */

	/**
	 * \brief Initialize all the resources of the game.
	 * \note WARNING: do not forget to delete the resources in the finalize method (even if the
	 * program is halting. Its a very useful practice).
	 */
	void initialize(void)
	{
		debug("Initializing game resources...");

		/* Initialize SDL before anything else. */
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			assert_exit("Failed to initialize SDL!!");
		}

		/* Creates the controller. */
		m_Control = new Controller;

		/* Creates the hard (aka: real) screen. */
		m_RealScreen = new Video(GAME_SCREEN_W, GAME_SCREEN_H, GAME_TITLE);
		/* Must initialize the hard video before creating virtual screens. */
		m_RealScreen->init();

		/* Creates a virtual video for the game board. Let it be at the origin 0, 0*/
		m_VirtualScreen_board = new VirtualVideo(m_RealScreen, GAME_BOARD_SCREEN_W, GAME_BOARD_SCREEN_H, GAME_BOARD_SCREEN_X, GAME_BOARD_SCREEN_Y);
		/* Initialize the game board, but don't start it yet. */
		m_VirtualScreen_board->init(false);

		m_VirtualScreen_menu = new VirtualVideo(m_RealScreen, GAME_MENU_SCREEN_W, GAME_MENU_SCREEN_H, GAME_MENU_SCREEN_X, GAME_MENU_SCREEN_Y);
		/* Initialize the game board, but don't start it yet. */
		m_VirtualScreen_menu->init(false);

		m_VirtualScreen_chatbar = new VirtualVideo(m_RealScreen, GAME_CHATBAR_SCREEN_W, GAME_CHATBAR_SCREEN_H, GAME_CHARTBAR_SCREEN_X, GAME_CHARTBAR_SCREEN_Y);
		/* Initialize the chat bat, but don't start it yet. */
		m_VirtualScreen_chatbar->init(false);

		m_GameBoard = new GameBoard(m_VirtualScreen_board);

		debug("Game resources were initialized.");
	}

	/**
	 * \brief Free all allocated resources for the game.
	 * \note Perhaps the most cautious way is to release the resources in the reverse order of its creation.
	 */
	void finalize(void)
	{
		debug("Releasing game resources...");

		delete m_VirtualScreen_menu;
		delete m_VirtualScreen_board;
		delete m_RealScreen;
		delete m_Control;
		SDL_Quit();

		debug("Game resources freed.");
	}


public:

	/* Messages. */
	void run_example3(void)
	{
		/* Initialize resources. */
		initialize();

		m_VirtualScreen_board->init();
		m_VirtualScreen_chatbar->init();
		m_Control->get_keyDown();

		m_VirtualScreen_board->fill_with_color(255,255,0);
		m_VirtualScreen_chatbar->fill_with_color(255,0,0);
		m_Control->get_keyDown();

		m_VirtualScreen_board->load_font("resources/fonts/lazy.ttf");
		m_VirtualScreen_chatbar->load_font("resources/fonts/lazy.ttf");
		m_Control->get_keyDown();

		uint32_t msg1 = m_VirtualScreen_board->write("vitoritoiroiror", {0,255,0}, 50,50);
		m_Control->get_keyDown();

		(void) m_VirtualScreen_chatbar->write("TESTESTESTE", {0,255,100}, 50,50);
		m_Control->get_keyDown();

		(void) m_VirtualScreen_chatbar->write("TAtatatatata dsada dasdasda", {0,255,100}, 50,70);
		m_Control->get_keyDown();

		m_VirtualScreen_board->fill_with_color(200,200,200);
		m_Control->get_keyDown();

		m_VirtualScreen_board->erase(msg1);
		m_VirtualScreen_board->fill_with_color(200,200,200);
		m_Control->get_keyDown();

		m_VirtualScreen_chatbar->remf_message_all();
		m_VirtualScreen_chatbar->fill_with_color(20,100,20);
		m_Control->get_keyDown();
//			//int x, y;
	//		SDL_Event event;
	/*	while(SDL_WaitEvent(&event)) {
		     switch (event.type) {
		            case SDL_ACTIVEEVENT: {
		                if ( event.active.state & SDL_APPACTIVE ) {
		                    if ( event.active.gain ) {
		                        printf("App activated\n");
		                    } else {
		                        printf("App iconified\n");
		                    }
		                }
		            }
		            break;

		            case SDL_MOUSEBUTTONDOWN: {
		                Uint8 *keys;

		                keys = SDL_GetKeyState(NULL);
		                if ( keys[SDLK_ESCAPE] == SDL_PRESSED ) {
		                    printf("Bye bye...\n");
		                    exit(0);
		                }
		                printf("Mouse button pressed\n");
		            }
		            break;

		            case SDL_QUIT: {
		                printf("Quit requested, quitting.\n");
		                exit(0);
		            }
		            break;
		        }

			debug(x <<", " <<y);
		}*/

		/* Free the resources. */
		finalize();
	}

	/**
	 * \brief Main class of class Main. Entry point.
	 * \note Initialize the resources. Start the engine. Finalize the resources before leaving.
	 */
	void run_example2(void)
	{
		/* Initialize resources. */
		initialize();

		m_RealScreen->start();

		m_Control->get_keyDown();

		m_VirtualScreen_menu->start();

		m_Control->get_keyDown();

		m_GameBoard->draw();

		m_Control->get_keyDown();

		m_VirtualScreen_menu->fill_with_color(0,0,255);

		m_Control->get_keyDown();

		m_VirtualScreen_chatbar->start();
		m_VirtualScreen_chatbar->fill_with_color(100,255,0);

		m_Control->get_keyDown();

		m_VirtualScreen_board->fill_with_color(255,100,100);

		m_Control->get_keyDown();

		/* Free the resources. */
		finalize();
	}

	/*
	 * \brief Runs a example of the Virtual Screens.
	 */
	void run_example()
	{
		/* Initialize resources. */
		initialize();

		m_RealScreen->start();

		m_Control->get_keyDown();

		m_VirtualScreen_menu->start();
		m_VirtualScreen_board->start();

		m_Control->get_keyDown();

		VisualElement *m = new VisualElement(0,0, WARRIOR_SPRITE);

		m_VirtualScreen_menu->add_visualElement(m);

		m_Control->get_keyDown();

		Viewpoints::paint_surface(m->get_viewpoint(), 255,0,0);

		m_Control->get_keyDown();

		m_VirtualScreen_menu->fill_with_color(0,255,0);

		m_Control->get_keyDown();

		m->add_offset(1, 10);

		m_Control->get_keyDown();

		m->add_offset(0, 50);

		m_Control->get_keyDown();

		m_VirtualScreen_board->fill_with_color(0,0,255);

		m_Control->get_keyDown();

		/* Free the resources. */
		finalize();
	}
};

/**
 * \brief Program entry point.
 */
int main(int argc, char* args[])
{
	Main game;

	//game.run_example();
	//game.run_example2();
	game.run_example3();

	return 0;
}
