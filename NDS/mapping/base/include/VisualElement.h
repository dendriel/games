/*
 * GameCharacter.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef VISUALELEMENT_H_
#define VISUALELEMENT_H_

#include <nds.h>

#include "util.h"

/* Definitions. */
#define SPRITE_LENGHT_BYTES 32*32

//!< Facility. Enumerate sprite positions.
typedef enum sprite_character_positions {
	SPRITE_FACING_NORTH_STEP_RIGHT = 0,
	SPRITE_FACING_NORTH_STOPPED,
	SPRITE_FACING_NORTH_STEP_LEFT,
	SPRITE_FACING_EAST_STEP_RIGHT,
	SPRITE_FACING_EAST_STOPPED,
	SPRITE_FACING_EAST_STEP_LEFT,
	SPRITE_FACING_SOUTH_STEP_RIGHT,
	SPRITE_FACING_SOUTH_STOPPED,
	SPRITE_FACING_SOUTH_STEP_LEFT,
	SPRITE_FACING_WEST_STEP_RIGHT,
	SPRITE_FACING_WEST_STOPPED,
	SPRITE_FACING_WEST_STEP_LEFT,
	SPRITE_FACING_NONE //!< Control purpose.
} sprite_character_positions;

/* Static values. */
static st_offset ms_Offset;

/**
 * \brief Game character class.
 */
class VisualElement {
private:
	st_offset& m_Pos;			//!< Absolute position.
	u8*  m_Charset_mem;			//!< Holds all the sprite of the element.
	u16* m_Sprite_mem;			//!< The current sprite that is being displayed.

public:

	/**
	 * \brief Class constructor.
	 */
	VisualElement(u8* charset = 0, st_offset& offset = ms_Offset);

	void update_sprite(const unsigned int offset_bytes);
};

#endif /* VISUALELEMENT_H_ */
