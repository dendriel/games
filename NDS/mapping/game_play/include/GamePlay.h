/*
 * GamePlay.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "GameMapProcessor.h"
#include "GameCharacter.h"
#include "GameController.h"
#include "GameScenery.h"


/**
 * \brief Handle the scenery loading and interactions.
 */
class GamePlay {
private:
	GameMapProcessor m_MapProcessor;
	GameCharacter *m_Character;
	GameController m_Controller;

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
	void start(const int level);

private:
	/**
	 * \brief Initialize basic system (map memory to video).
	 */
	void init_basics(void);

	/**
	 * \brief Plays the specified scenery.
	 */
	void run_level();

	/**
	 * \brief Create the scenery matching with the level.
	 */
	GameScenery *create_scenery(en_scen_level level);
};

#endif /* GAMEPLAY_H_ */
