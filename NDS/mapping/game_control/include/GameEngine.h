/*
 * GameEngine.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include "GameMenu.h"
#include "GameCredits.h"
#include "GamePassword.h"
#include "scenery.h"

/**
 * \brief Main class. Hold the gaming interaction.
 */
class GameEngine {
private:
	GameMenu m_Menu;
	GameCredits m_Credits;
	GamePassword m_Password;

public:
	/**
	 * \brief Main game line.
	 */
	void start_game(void);

private:
	/**
	 * \brief Executes the user choice from the game menu.
	 * \parameter menu_choice The user's choice.
	 */
	void execute_operation(const en_menu_options menu_choice);

	/**
	 * \brief Start a new game.
	 * \parameter Starting level of the game.
	 */
	void execute_opt_start_game(const en_scen_level level);

	/**
	 * \brief Splash screen.
	 */
	void display_splash(void);
};


#endif /* GAMEENGINE_H_ */
