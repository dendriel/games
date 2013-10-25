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

	std::queue<st_trigger> m_ActionsQueue;

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
	void dequeue_actions(void);

	/**
	 * \brief Execute action and update the received parameter to the next action.
	 * \parameter action Action to execute.
	 */
	void execute_action(en_action& action);

	/**
	 * \brief Character touch action.
	 */
	void touch_action(void);
};

#endif /* GAMEPLAY_H_ */
