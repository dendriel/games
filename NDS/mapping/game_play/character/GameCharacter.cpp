/*
 * GameCharacter.cpp
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#include "GameCharacter.h"
#include "timming.h"

#define CHAR_STEP_DELAY 2 // vsync cycles

GameCharacter::GameCharacter(u8 *charset, size_t step_len_pixels, int x, int y):
VisualElement(charset, m_Pos),
m_Pos(x, y),
m_Facing(W_DOWN),
m_StepLen_pixes(step_len_pixels),
m_Step(1)
{
	update_sprite(0);
	update_oam();
}

void GameCharacter::move(en_facing direction)
{
	// TODO: this code is just for testing purpose.
	unsigned int  offset = 6*SPRITE_LENGHT_BYTES;

	switch (direction) {

	case W_UP:
		m_Facing = W_UP;
		if(m_Step)
			offset =  2*SPRITE_LENGHT_BYTES;
		else
			offset =  1*SPRITE_LENGHT_BYTES;
		break;

	case W_RIGHT:
		m_Facing = W_RIGHT;
		if(m_Step)
			offset = 4*SPRITE_LENGHT_BYTES;
		else
			offset = 3*SPRITE_LENGHT_BYTES;
		break;

	case W_DOWN:
		m_Facing = W_DOWN;
		if(m_Step) {
			offset = 6*SPRITE_LENGHT_BYTES;
			update_sprite(offset);
			GSLEEP(CHAR_STEP_DELAY);
			offset = 8*SPRITE_LENGHT_BYTES;
			update_sprite(offset);
			GSLEEP(CHAR_STEP_DELAY);
			offset = 7*SPRITE_LENGHT_BYTES;
			update_sprite(offset);
		}
		else
			offset = 6*SPRITE_LENGHT_BYTES;
		break;

	case W_LEFT:
		m_Facing = W_LEFT;
		if(m_Step)
			offset = 10*SPRITE_LENGHT_BYTES;
		else
			offset = 9*SPRITE_LENGHT_BYTES;
		break;

	default:
		break;

	}

	update_sprite(offset);

	/* Change next step. */
	m_Step = !m_Step;
}
