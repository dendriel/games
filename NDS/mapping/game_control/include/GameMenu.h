/*
 * GameMenu.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEMENU_H_
#define GAMEMENU_H_

typedef enum {
	MENU_OPT_EXIT = 1,
	MENU_OPT_START_GAME,
} en_menu_options;

// TODO
/**
 * \brief Display menu and get user choice.
 */
class GameMenu {

public:

	/**
	 * \brief Shows the menu in the screen.
	 */
	void display(void);

	/**
	 * \brief Lets the user interact to change an option.
	 */
	en_menu_options get_choice(void);
};


#endif /* GAMEMENU_H_ */
