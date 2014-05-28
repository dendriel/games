#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <tr1/cstdint>

#include "SDL/SDL.h"

#include "Video.h"
#include "VirtualVideo.h"
#include "Viewpoints.h"
//#include "GameBoard.h"
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
	VirtualVideo *m_GameBoard;	//!< Video object to represent the game board.
	VirtualVideo *m_GameMenu;	//!< Video object to represent the game menu.

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
		/* Must initialize the hard video before creating virtual screens. But not start it yet. */
		m_RealScreen->init(false);

		/* Creates a virtual video for the game board. Let it be at the origin 0, 0*/
		m_GameBoard = new VirtualVideo(m_RealScreen, GAME_BOARD_SCREEN_W, GAME_BOARD_SCREEN_H, GAME_BOARD_SCREEN_X, GAME_BOARD_SCREEN_Y);
		/* Initialize the game board, but don't start it yet. */
		m_GameBoard->init(false);

		m_GameMenu = new VirtualVideo(m_RealScreen, GAME_MENU_SCREEN_W, GAME_MENU_SCREEN_H, GAME_MENU_SCREEN_X, GAME_MENU_SCREEN_Y);
		/* Initialize the game board, but don't start it yet. */
		m_GameMenu->init(false);

		debug("Game resources were initialized.");
	}

	/**
	 * \brief Free all allocated resources for the game.
	 * \note Perhaps the most cautious way is to release the resources in the reverse order of its creation.
	 */
	void finalize(void)
	{
		debug("Releasing game resources...");

		delete m_GameMenu;
		delete m_GameBoard;
		delete m_RealScreen;
		delete m_Control;
		SDL_Quit();

		debug("Game resources freed.");
	}


public:
	/**
	 * \brief Main class of class Main. Entry point.
	 * \note Initialize the resources. Start the engine. Finalize the resources before leaving.
	 */
	void run(void)
	{
		/* Initialize resources. */
		initialize();

		m_RealScreen->start();

		m_Control->get_keyDown();

		m_GameMenu->start();
		m_GameBoard->start();

		m_Control->get_keyDown();

		VisualElement *m = new VisualElement(0,0, WARRIOR_SPRITE);

		m_GameMenu->add_visualElement(m);

		m_Control->get_keyDown();

		Viewpoints::paint_surface(m->get_viewpoint(), 255,0,0);

		m_Control->get_keyDown();

		m_GameMenu->fill_with_color(0,255,0);

		m_Control->get_keyDown();

		m->add_offset(1, 10);

		m_Control->get_keyDown();

		m->add_offset(0, 50);

		m_Control->get_keyDown();

		m_GameBoard->fill_with_color(0,0,255);

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

	game.run();

	return 0;
}
