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

	void update_oam(void);
};

#endif /* VISUALELEMENT_H_ */
