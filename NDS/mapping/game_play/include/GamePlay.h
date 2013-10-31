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
#include "Trigger.h"
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
	 * \brief Character touch action.
	 */
	void touch_action(void);

	/**
	 * \brief Give an object to the character. Nothing will happen if there is no room in the
	 * inventory. The object reference will be removed from the original place (scenery object list,
	 * for example), and added into the character inventory.
	 * \parameter object_id What object will be added to the character inventory.
	 */
	void give_object_action(const long& object_id);

	/**
	 * \brief Check if the character have the object and, if it has, push the next reaction into the queue.
	 * \parameter object_id What object will be added to the character inventory.
	 * \parameter next The next trigger in the chain to be executed.
	 */
	void check_for_object_action(const long& object_id, Trigger *next=NULL);

	/**
	 * \brief Remove the object from the player inventory.
	 * \parameter object_id What object will be removed from the character inventory.
	 * \parameter next The next trigger in the chain to be executed.
	 */
	void remove_object_action(const long& object_id, Trigger *next=NULL);

	/**
	 * \brief Change the object displayed sprite.
	 * \parameter object_id What object will be removed from the character inventory.
	 * \parameter new_sprite The sprite position to be displayed of the object char set.
	 * \parameter next The next trigger in the chain to be executed.
	 */
	void change_sprite_action(const long& object_id, const int& new_sprite, Trigger *next=NULL);

	/**
	 * \brief Change the current trigger from an object to the given one (the current will be deactivate and the new will be activated).
	 * \parameter object_id What object will be removed from the character inventory.
	 * \parameter reaction The reaction that will be activated.
	 * \parameter next The next trigger in the chain to be executed.
	 */
	void change_reaction_action(const long& object_id, const en_action& reaction, Trigger *new_trigger);
};

#endif /* GAMEPLAY_H_ */
