/*
 * game_actions.h
 *
 *  Created on: 02/10/2013
 *      Author: vitor
 */

#ifndef GAME_ACTIONS_H_
#define GAME_ACTIONS_H_

/**
 *  Map game actions.
 *  Note: Initially created this header so GameController can parser the controller actions to
 *  in-game actions.
 */


typedef enum en_action {
	//! Walking actions.
	ACTION_WALK_NORTH,
	ACTION_WALK_SOUTH,
	ACTION_WALK_EAST,
	ACTION_WALK_WEST,
	ACTION_TOUCH,
	ACTION_GIVE_OBJECT,
	ACTION_CONSOLE_CLEAR, //!< Only for develop time.
	ACTION_NONE				//!< No action selected.
} en_action;

//! Define a structure to be used as an action that triggers another action.
typedef struct st_trigger {
	en_action trigger;	//!< What action is the trigger.
	en_action reaction;	//!< The re-action.
	int charges;		//!< How much times can repeat the trigger. (-1 will be infinite times)
	// Some basic elements that the action may use.
	struct {
		long id;
		void *data;	// maybe will be useful. just an idea so far.
	};
	st_trigger(en_action _t=ACTION_NONE, en_action _a=ACTION_NONE, int _ch=0, long _id=0, void *_dt=NULL):
		trigger(_t),
		reaction(_a),
		charges(_ch),
		id(_id),
		data(_dt){}
} st_trigger;

//! Post fix to increment the action.
inline en_action& operator++(en_action& orig, int)
{
	orig = static_cast<en_action>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* GAME_ACTIONS_H_ */
