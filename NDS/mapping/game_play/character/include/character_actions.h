/*
 * character_actions.h
 *
 *  Created on: 02/10/2013
 *      Author: vitor
 */

#ifndef CHARACTER_ACTIONS_H_
#define CHARACTER_ACTIONS_H_

/**
 *  Map character actions.
 *  Note: created this header so GameController can parser the controller actions to in-game actions.
 */
//!
typedef enum en_char_action {
	//!< Walking actions.
	ACTION_WALK_NORTH,
	ACTION_WALK_SOUTH,
	ACTION_WALK_EAST,
	ACTION_WALK_WEST,
	ACTION_NONE				//!< No action selected.
} en_char_action;


//!< Postfix to increment the action.
inline en_char_action& operator++(en_char_action& orig, int)
{
	orig = static_cast<en_char_action>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* CHARACTER_ACTIONS_H_ */
