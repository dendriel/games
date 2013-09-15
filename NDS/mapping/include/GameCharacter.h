/*
 * GameCharacter.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include <nds.h>

#include "util.h"


class GameCharacter {
private:
	st_offset m_Pos;		//!< Position of the character in the screen (not the scenery).
	u16* m_Sprite_mem;			//!< The current character set sprite that is being displayed.
	u8*  m_Charset_mem;			//!< Holds all the sprite of the character.
	en_facing m_Facing;			//!< Character facing direction.

public:

	/**
	 * \brief Class constructor.
	 */
	GameCharacter(u8* charset = 0, int x = 0, int y = 0);

	/**
	 * \brief Move the character.
	 * \parameter direction Which direction to move.
	 */
	void move(en_facing direction);
	void move(const int x, const int y);
};


#endif /* GAMECHARACTER_H_ */
