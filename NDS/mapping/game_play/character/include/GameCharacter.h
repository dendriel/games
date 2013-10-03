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
	st_offset m_Pos_absolute;	//!< Position of the character in the screen (not the scenery. Absolute position in Pixels).
	st_offset m_Pos_relative;	//!< Position of the character in the screen (not the scenery. Relative position in Pixels).
	en_facing m_Facing;				//!< Facing direction.
	const size_t m_StepLen_pixes;	//!< Total Movement size in pixels. The right step will have an increment of 1 pixel, so the total walked pixels is a full tile size.
	GameMapProcessor *m_MapProcessor;

public:
	/**
	 * \brief Class constructor.
	 * \parameter x Character horizontal absolute position.
	 * \parameter y Character vertical absolute position.
	 */
	GameCharacter(u8 *charset = 0, size_t step_len_pixels = 0, int x = 0, int y = 0);

	/**
	 * \brief Add the map processor reference.
	 */
	void set_map_processor(GameMapProcessor& processor);

	/**
	 * \brief Execute action and update the received parameter to the next action.
	 * \action Action to execute.
	 */
	void execute_action(en_char_action& action, const unsigned int interaction);

	/**
	 * \brief Move the character.
	 * \parameter action Contains information about where to move. Also will be change to the next action.
	 * \parameter direction Which direction to move.
	 */
	void move(en_char_action& action);
	void move(const int x, const int y);

	/**
	 * \brief Returns step lenght in pixels.
	 */
	inline size_t get_StepLen_pixels(void)
	{
		return m_StepLen_pixes;
	}

	inline void set_m_Pos_relative(const int x_pixels, const int y_pixels)
	{
		m_Pos_relative.x = x_pixels;
		m_Pos_relative.y = y_pixels;
	}

private:
	/**
	 * \brief Move the map and update character relative position.
	 * \parameter x Character horizontal relative position.
	 * \parameter y Character vertical relative position.
	 */
	void move_background(const int x_pixels, const int y_pixels);

};

#endif /* GAMECHARACTER_H_ */
