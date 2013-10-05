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
 *
 *  Game loop will held at maximum of 5 actions. Thus, can't be more than this number of sequenced
 *  actions to process. If there is more than 5, put a define as bounder to limit the action.
 *
 *  Note: created this header so GameController can parser the controller actions to in-game actions.
 */
//!
typedef enum en_char_action {
	//!< Walkin actions.
	ACTION_WALK_NORTH_RIGHT,
	ACTION_WALK_NORTH_LEFT,
	ACTION_WALK_NORTH_RIGHT2,
	ACTION_WALK_NORTH_LEFT2,
	ACTION_WALK_NORTH_END,
	ACTION_WALK_SOUTH_RIGHT,
	ACTION_WALK_SOUTH_LEFT,
	ACTION_WALK_SOUTH_RIGHT2,
	ACTION_WALK_SOUTH_LEFT2,
	ACTION_WALK_SOUTH_END,
	ACTION_WALK_EAST_RIGHT,
	ACTION_WALK_EAST_LEFT,
	ACTION_WALK_EAST_RIGHT2,
	ACTION_WALK_EAST_LEFT2,
	ACTION_WALK_EAST_END,
	ACTION_WALK_WEST_RIGHT,
	ACTION_WALK_WEST_LEFT,
	ACTION_WALK_WEST_RIGHT2,
	ACTION_WALK_WEST_LEFT2,
	ACTION_WALK_WEST_END,
	ACTION_WALK_STAY,		//!< Walk action control.
	// ADD NEXT ACTION HERE.
	ACTION_NONE				//!< No action selected.
} en_char_action;


//!< Postfix to increment the action.
inline en_char_action& operator++(en_char_action& orig, int)
{
	orig = static_cast<en_char_action>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* CHARACTER_ACTIONS_H_ */
