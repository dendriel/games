/*
 * GameCharacter.cpp
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#include "GameCharacter.h"

/* References */
#include "nds/arm9/sprite.h"


/*************************************************************************************************/
/* Public Functions Declaration																	 */
/*************************************************************************************************/

GameCharacter::GameCharacter(u8 *charset, int x, int y):
m_Charset_mem((u8*)charset),
m_Facing(W_DOWN)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Sprite_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	u8* offset = m_Charset_mem + 6*32*32;
	dmaCopy(offset, m_Sprite_mem, 32*32);

	oamSet(&oamMain, 0, m_Pos.x, m_Pos.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
		m_Sprite_mem, -1, false, false, false, false, false);

}

//---------------------------------------------------------------------
// Animating a man requires us to copy in a new frame of data each time
//---------------------------------------------------------------------
void GameCharacter::move(en_facing direction)
{
	// TODO: this code is just for testing purpose.
	u8* offset = m_Charset_mem + 32*32;

	switch (direction) {

	case W_UP:
		m_Facing = W_UP;
		offset = m_Charset_mem + 2*32*32;
		break;

	case W_RIGHT:
		m_Facing = W_RIGHT;
		offset = m_Charset_mem + 3*32*32;
		break;

	case W_DOWN:
		m_Facing = W_DOWN;
		offset = m_Charset_mem + 6*32*32;
		break;

	case W_LEFT:
		m_Facing = W_LEFT;
		offset = m_Charset_mem + 9*32*32;
		break;

	default:
		break;

	}

	dmaCopy(offset, m_Sprite_mem, 32*32);


	oamSet(&oamMain, 0, m_Pos.x, m_Pos.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
		m_Sprite_mem, -1, false, false, false, false, false);
}

//---------------------------------------------------------------------
// Animating a man requires us to copy in a new frame of data each time
//---------------------------------------------------------------------
void GameCharacter::move(const int x, const int y)
{
	/*switch (direction) {

	}*/
	//int frame = 3 + 1 * 3;

	u8* offset = m_Charset_mem + 32*32;
	dmaCopy(offset, m_Sprite_mem, 32*32);

	oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
		m_Sprite_mem, -1, false, false, false, false, false);
}

/*************************************************************************************************/
/* Private Functions Declaration																 */
/*************************************************************************************************/
