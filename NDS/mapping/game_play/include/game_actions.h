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
	ACTION_CHECK_OBJECT,
	ACTION_CHECK_REMOVE_OBJECT,
	ACTION_REMOVE_OBJECT,
	ACTION_CHANGE_SPRITE,
	ACTION_CONSOLE_CLEAR, //!< Only for develop time.
	ACTION_NONE				//!< No action selected.
} en_action;

//! Define a structure to be used as an action that triggers another action.
typedef struct st_trigger {
	en_action trigger;	//!< What action is the trigger.
	en_action reaction;	//!< The re-action.
	int charges;		//!< How much times can repeat the trigger. (-1 will be infinite times)
	st_trigger *next_reaction;	//!< Use to make reaction chains.
	// Some basic elements that the action may use.
	struct {
		long gen_id;	// Generic id for actions use (the id of given object, for example).
		void *data;		// Maybe will be useful. just an idea so far.
	};
	st_trigger(en_action t=ACTION_NONE, en_action a=ACTION_NONE, int ch=0, st_trigger *next=NULL, long id=0, void *dt=NULL):
		trigger(t),
		reaction(a),
		charges(ch),
		next_reaction(next),
		gen_id(id),
		data(dt){}
} st_trigger;

//! Post fix to increment the action.
inline en_action& operator++(en_action& orig, int)
{
	orig = static_cast<en_action>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* GAME_ACTIONS_H_ */
