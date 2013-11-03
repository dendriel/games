/*
 * GamePlay.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <queue>

#include "GameMapProcessor.h"
#include "GameCharacter.h"
#include "GameController.h"
#include "GameScenery.h"
#include "triggers.h"
#include "scenery.h"
#include "game_actions.h"


/**
 * \brief Handle the scenery loading and interactions.
 */
class GamePlay {
private:
	GameMapProcessor m_MapProcessor;
	GameController m_Controller;
	GameScenery *m_Scenery;
	GameCharacter *m_Character;

	std::queue<Trigger *> m_ActionsQueue;

public:
	/**
	 * \brief Class constructor.
	 */
	GamePlay(void);

	/**
	 * \brief Class destructor.
	 */
	~GamePlay(void);

	/**
	 * \brief Starts the in-game interaction.
	 * \parameter level The starting level (if a correct password was inserted).
	 */
	void start(const en_scen_level level);

private:
	/**
	 * \brief Initialize basic system (map memory to video).
	 */
	void init_basics(void);

	/**
	 * \brief Plays the specified scenery.
	 */
	void load_level(const en_scen_level level);

	/**
	 * \brief Free current scenery resources.
	 */
	void unload_level(void);

	/**
	 * \brief Create the scenery matching with the level.
	 * \parameter level The scenery reference.
	 * \return The created scenery.
	 */
	GameScenery *create_scenery(const en_scen_level level);

	/**
	 * \brief Get and process gaming actions.
	 * \return TODO: should return the ending state of the level.
	 */
	void play_game_loop(void);

	/**
	 * \brief Update the character position (use at the start of the scenery to correctly place the character).
	 */
	void set_character_relative_pos_32px(const int& x, const int& y);

	/**
	 * \brief Move the map and update character relative position.
	 * \parameter x Character horizontal relative position.
	 * \parameter y Character vertical relative position.
	 */
	void move_background_8px(const int& x, const int& y);

	/**
	 * \brief Verify if the next character movement is colliding with an object.
	 * \parameter coll_char_rect The collision rectangle in the new position to be checked.
	 * \return true if collision occur; false otherwise
	 */
	bool check_object_collision(st_rect& coll_char_rect);

	/**
	 * \brief Dequeue and execute all enqueued actions.
	 */
	void execute_queued_reactions(void);

	/**
	 * \brief Execute action and update the received parameter to the next action.
	 * \parameter action Action to execute.
	 * \parameter trigger Data from a triggered reaction.
	 */
	void execute_action(en_action action, Trigger *trigger=NULL);

	/**
	 * \brief Move the character.
	 * \parameter direction Which direction to move.
	 * \parameter move_cooldown Cool down between moving action.
	 */
	void move_character_action(en_action& direction, const unsigned int& move_cooldown);

	/**
	 * \brief Character touch action.
	 */
	void touch_action(void);

	/**
	 * \brief Give an object to the character. Nothing will happen if there is no room in the
	 * inventory. The object reference will be removed from the original place (scenery object list,
	 * for example), and added into the character inventory.
	 * \parameter trigger Data for execute reaction.
	 *
	 * \note: Trigger setup:
	 *
	 * new Trigger_change_sprite(object_id,					//! Object that will be given.
	 *							next_reaction,				//! Chain reaction (optional);
	 *							ACTION_NONE,				//! Triggering action (optional).
	 *							false,						//! Enabled flag (optional).
	 *							-1);						//! Repeat flag (optional);
	 */
	void give_object_action(Trigger_give_object *trigger);

	/**
	 * \brief Check if the character have the object and, if it has, push the next reaction into the queue.
	 * \parameter trigger Data for execute reaction.
	 *
	 * \note: Trigger setup:
	 *
	 * new Trigger_check_object(object_id,					//! Object to verify in character's inventory.
	 *							next_reaction,				//! Chain reaction (optional);
	 *							ACTION_NONE,				//! Triggering action (optional).
	 *							false,						//! Enabled flag (optional).
	 *							-1);						//! Repeat flag (optional);
	 *
	 *
	 */
	void check_object_action(Trigger_check_object *trigger);

	/**
	 * \brief Remove the object from the character inventory.
	 * \parameter trigger Data for execute reaction.
	 *
	 * \note: Trigger setup:
	 *
	 * new Trigger_remove_object(object_id,					//! Object to remove from character.
	 *							next_reaction,				//! Chain reaction (optional);
	 *							ACTION_NONE,				//! Triggering action (optional).
	 *							false,						//! Enabled flag (optional).
	 *							-1);						//! Repeat flag (optional);
	 */
	void remove_object_action(Trigger_remove_object *trigger);

	/**
	 * \brief Change the object displayed sprite.
	 * \parameter trigger Data for execute reaction.
	 *
	 * \note: Trigger setup:
	 *
	 * new Trigger_change_sprite(object_id,					//! Object to update.
	 *							new_sprite,					//! New sprite position.
	 *							next_reaction,				//! Chain reaction (optional);
	 *							ACTION_NONE,				//! Triggering action (optional).
	 *							false,						//! Enabled flag (optional).
	 *							-1);						//! Repeat flag (optional);
	 */
	void change_sprite_action(Trigger_change_sprite *trigger);

	/**
	 * \brief Change the current trigger from an object to the given one (the current will be deactivate and the new will be activated).
	 * \parameter trigger Data for execute reaction.
	 *
	 * \note: Trigger setup:
	 *
	 * new Trigger_change_reaction(object_id,					//! Object that will have the reaction changed.
	 *								reaction,					//! Reaction type that will be disabled.
	 *								new_reaction,				//! Trigger to be enabled.
	 *								trigger,					//! Trigger that will be enabled.
	 *								ACTION_NONE,				//! Triggering action (optional).
	 *								false,						//! Enabled flag (optional).
	 *								-1);						//! Repeat flag (optional);
	 */
	void change_reaction_action(Trigger_change_reaction *trigger);

	/**
	 * \brief Delay some time.
	 * \parameter trigger The trigger that will be re-queued until the delay time expires.
	 * \note Can be used to delay some reactions.
	 *
	 * \note Trigger setup:
	 *
	 * new Trigger_delay(time_cycles,				//! How much cycles to delay.
	 *					next_reaction,				//! Chain reaction.
	 *					ACTION_NONE,				//! Triggering action (optional).
	 *					false,						//! Enabled flag (optional).
	 *					-1);						//! Repeat flag (optional);
	 */
	void delay_action(Trigger_delay *trigger);
};

#endif /* GAMEPLAY_H_ */
