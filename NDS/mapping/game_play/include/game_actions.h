/*
 * game_actions.h
 *
 *  Created on: 02/10/2013
 *      Author: vitor
 */

#ifndef GAME_ACTIONS_H_
#define GAME_ACTIONS_H_

#include <iostream>

/**
 *  Map game actions.
 *  Note: Initially created this header so GameController can parser the controller actions to
 *  in-game actions.
 */


typedef enum en_action {
	//! Walking actions.
	ACTION_WALK_NORTH = 0,
	ACTION_WALK_SOUTH,
	ACTION_WALK_EAST,
	ACTION_WALK_WEST,
	ACTION_RUN_NORTH,
	ACTION_RUN_SOUTH, // 5
	ACTION_RUN_EAST,
	ACTION_RUN_WEST,
	ACTION_TOUCH,
	ACTION_GIVE_OBJECT,
	ACTION_CHECK_OBJECT, // 10
	ACTION_REMOVE_OBJECT,
	ACTION_CHANGE_SPRITE,
	ACTION_CHANGE_REACTION,
	ACTION_DELAY,
	ACTION_CONSOLE_CLEAR, //!< Only for develop time.
	ACTION_NONE			 //!< 11 No action selected.
} en_action;

//! Post fix to increment the action.
inline en_action& operator++(en_action& orig, int)
{
	orig = static_cast<en_action>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* GAME_ACTIONS_H_ */
