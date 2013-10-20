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
/* Public Functions Declaration                                                                  */
/*************************************************************************************************/

VisualElement::VisualElement(st_offset *offset, u8* charset)
{
	if (this->alloc_SpriteData(&m_SpritePosition, charset, offset) == false) {
		debug("There is no more free sprite positions to use.");
		return;
	}

	debug("Allocated sprite pos: %d", m_SpritePosition);
}

VisualElement::~VisualElement(void)
{
	this->free_SpriteData(m_SpritePosition);

	debug("Freed sprite pos: %d", m_SpritePosition);
}

/*************************************************************************************************/

void VisualElement::update_sprite(const unsigned int offset_bytes)
{
	st_sprite& sprite = s_SpritePositions[m_SpritePosition];

	u8 *data_offset = sprite.charset_data + offset_bytes;
	dmaCopy(data_offset, sprite.mem_addr, SPRITE_LENGHT_BYTES);

	oamSet(&oamMain,
			m_SpritePosition,
			s_SpritePositions[m_SpritePosition].offset->x, s_SpritePositions[m_SpritePosition].offset->y,
			0, 0,
			SpriteSize_32x32,
			SpriteColorFormat_256Color,
			sprite.mem_addr,
			-1, false, false, false, false, false);
}

/*************************************************************************************************/

void VisualElement::update_position(void)
{
	for (unsigned short i = 0; i < SPRITE_POSITIONS; ++i) {

		st_sprite& sprite = s_SpritePositions[i];

		if (sprite.in_use == false) {
			continue;
		}

		int new_x = sprite.offset->x;
		int new_y = sprite.offset->y;

		/* Give extra offset to correctly place the other sprite. */
		if (i != SPRITE_PIVOT_INDEX) {
			//debug("new: %d,%d", new_x, new_y);
			new_x +=  s_SpritePositions[SPRITE_PIVOT_INDEX].offset->x - TILE_8PX_TO_PX(VisualElement::s_PivotOffset_8px->x);
			new_y +=  s_SpritePositions[SPRITE_PIVOT_INDEX].offset->y - TILE_8PX_TO_PX(VisualElement::s_PivotOffset_8px->y);
			//debug("bef: %d,%d", new_x, new_y);

			/* Verify if the sprite is inside the showing bounds (otherwise, it will be appearing
			 * every multiples of "screen size offset")
			 */
			if ( ((new_x + TILE_SIZE_32PX) < 0) || ((new_y + TILE_SIZE_32PX) < 0) ||
					(new_x > SCREEN_WIDTH) || (new_y > SCREEN_HEIGHT)) {
				oamClearSprite(&oamMain, i);
				continue;
			}
		}

		oamSet(&oamMain,
				i,
				new_x, new_y,
				0, 0,
				SpriteSize_32x32,
				SpriteColorFormat_256Color,
				sprite.mem_addr,
				-1, false, false, false, false, false);

		//debug("show sprite: %d", i);
	}
}

/*************************************************************************************************/

bool VisualElement::alloc_SpriteData(int *sprite_position, u8 *charset, st_offset *offset)
{
	for (unsigned short i = 0; i < SPRITE_POSITIONS; ++i) {

		if (VisualElement::s_SpritePositions[i].in_use == false) {

			VisualElement::s_SpritePositions[i].in_use = true;
			VisualElement::s_SpritePositions[i].charset_data = charset;
			VisualElement::s_SpritePositions[i].offset = offset;

			*sprite_position = i;

			return true;
		}
	}

	return false;
}

/*************************************************************************************************/

void VisualElement::free_SpriteData(const int sprite_position)
{
	VisualElement::s_SpritePositions[sprite_position].in_use = false;
}

/*************************************************************************************************/

