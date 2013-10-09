/*
 * GameCharacter.h
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include "VisualElement.h"
#include "GameMapProcessor.h"
#include "character_actions.h"


class GameCharacter: private VisualElement {
private:
	st_offset m_Pos_absolute_px;	//!< Position of the character in the screen (not the scenery. Absolute position in Pixels).
	st_offset m_Pos_relative_8px;	//!< Position of the character in the screen (not the scenery. Relative position).
	en_facing m_Facing;				//!< Facing direction.
	GameMapProcessor *m_MapProcessor;

	/* Actions cool down. */
	unsigned short m_ActionMove_cooldown;	//!< Cool down before moving action.

public:
	/**
	 * \brief Class constructor.
	 * \parameter x_px Character horizontal absolute position.
	 * \parameter y_px Character vertical absolute position.
	 */
	GameCharacter(u8 *charset = 0, int x_px = 0, int y_px = 0);

	/**
	 * \brief Add the map processor reference.
	 */
	void set_map_processor(GameMapProcessor& processor);

	/**
	 * \brief Execute action and update the received parameter to the next action.
	 * \parameter action Action to execute.
	 */
	void execute_action(en_char_action& action);

	/**
	 * \brief Move the character.
	 * \parameter action Contains information about where to move. Also will be change to the next action.
	 * \parameter direction Which direction to move.
	 */
	void move(en_char_action& action);
	void move(const int x, const int y);

	/**
	 * \brief Set character relative position. Also move the map.
	 */
	void set_relative_pos_32px(const int x, const int y);

private:
	/**
	 * \brief Move the map and update character relative position.
	 * \parameter x Character horizontal relative position.
	 * \parameter y Character vertical relative position.
	 */
	void move_background_8px(const int x, const int y);

	/**
	 * \brief Update all actions cool down.
	 */
	void update_actions_cooldown(void);

};

#endif /* GAMECHARACTER_H_ */
