/*
 * VisualElement.cpp
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#include "VisualElement.h"

/* References */
#include "nds/arm9/sprite.h"
#include "util.h"


/*************************************************************************************************/
/* Public Functions Declaration																	 */
/*************************************************************************************************/

VisualElement::VisualElement(u8* charset, st_offset& offset):
m_Pos(offset),
m_Charset_mem((u8*)charset)
{
	m_Sprite_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/*************************************************************************************************/

void VisualElement::update_sprite(const unsigned int offset_bytes)
{
	u8 *data_offset = m_Charset_mem + offset_bytes;
	dmaCopy(data_offset, m_Sprite_mem, SPRITE_LENGHT_BYTES);
	update_oam();
}

/*************************************************************************************************/

void VisualElement::update_oam(void)
{
	oamSet(&oamMain, 0, m_Pos.x, m_Pos.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
			m_Sprite_mem, -1, false, false, false, false, false);
	debug("update_oam; charset: %p; sprite_mem: %p", m_Charset_mem, m_Sprite_mem);
}
