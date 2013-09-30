/*
 * GameEngine.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEENGINE_CPP_
#define GAMEENGINE_CPP_

#include "GameEngine.h"
#include "GamePlay.h"

/*************************************************************************************************/

void GameEngine::start_game(void)
{
	en_menu_options menu_choice;

	this->display_splash();

	m_Menu.display();
	menu_choice = m_Menu.get_choice();
	this->execute_operation(menu_choice);
}

/*************************************************************************************************/

void GameEngine::execute_operation(const en_menu_options menu_choice)
{
	switch (menu_choice) {
		case MENU_OPT_EXIT:
			/* Leave the game. */
			break;
		case MENU_OPT_START_GAME:
			/* Start the game play. */
			this->execute_opt_start_game(-1);
			break;
		default:
			break;
	}
}

/*************************************************************************************************/

void GameEngine::execute_opt_start_game(const int level)
{
	GamePlay game_play;
	game_play.start(level);
}

/*************************************************************************************************/

void GameEngine::display_splash(void)
{
	;;
}

#endif /* GAMEENGINE_CPP_ */
