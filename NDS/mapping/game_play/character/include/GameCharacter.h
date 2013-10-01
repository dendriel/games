/*
 * GameCharacter.h
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include "VisualElement.h"

class GameCharacter: private VisualElement {
private:
	st_offset m_Pos;				//!< Position of the character in the screen (not the scenery. Absolute position).
	en_facing m_Facing;				//!< Facing direction.
	const size_t m_StepLen_pixes;	//!< Total Movement size in pixels.
	bool m_Step;					//!< Next step foot.

public:
	/**
	 * \brief Class constructor.
	 */
	GameCharacter(u8 *charset = 0, size_t step_len_pixels = 0, int x = 0, int y = 0);

	/**
	 * \brief Move the character.
	 * \parameter direction Which direction to move.
	 */
	void move(en_facing direction);
	void move(const int x, const int y);

	/**
	 * \brief Returns step lenght in pixels.
	 */
	inline size_t get_StepLen_pixels(void)
	{
		return m_StepLen_pixes;
	}

};

#endif /* GAMECHARACTER_H_ */
