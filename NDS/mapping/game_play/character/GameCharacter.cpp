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
m_MapProcessor(0)
{
	update_sprite(0);
}

/*************************************************************************************************/

void GameCharacter::set_map_processor(GameMapProcessor& processor)
{
	m_MapProcessor = &processor;
}

/*************************************************************************************************/

void GameCharacter::execute_action(en_char_action& action, const unsigned int interaction)
{
	switch(action) {

	case ACTION_WALK_NORTH_RIGHT:
		this->move(action);
		break;
	case ACTION_WALK_NORTH_LEFT:
		if (interaction >= 4) {
			this->move(action);
		}
		break;
	case ACTION_WALK_NORTH_END:
	case ACTION_WALK_SOUTH_RIGHT:
	case ACTION_WALK_SOUTH_LEFT:
	case ACTION_WALK_SOUTH_END:
	case ACTION_WALK_EAST_RIGHT:
	case ACTION_WALK_EAST_LEFT:
	case ACTION_WALK_EAST_END:
	case ACTION_WALK_WEST_RIGHT:
	case ACTION_WALK_WEST_LEFT:
	case ACTION_WALK_WEST_END:
		this->move(action);
		break;

	case ACTION_NONE:
	default:
		break;
	}
}

/*************************************************************************************************/

void GameCharacter::move(en_char_action& action)
{
	//static sprite_character_positions previous_sprite_position = SPRITE_FACING_NONE;
	sprite_character_positions sprite_position = SPRITE_FACING_NORTH_STEP_RIGHT;

	switch(action) {

	case ACTION_WALK_NORTH_RIGHT:
		sprite_position = SPRITE_FACING_NORTH_STEP_RIGHT;
		action = ACTION_WALK_NORTH_LEFT;
		m_MapProcessor->scroll_Background(0, -1*m_StepLen_pixes);
		break;

	case ACTION_WALK_NORTH_LEFT:
		sprite_position = SPRITE_FACING_NORTH_STEP_LEFT;
		action = ACTION_WALK_NORTH_END;
		m_MapProcessor->scroll_Background(0, -1*m_StepLen_pixes);
		break;

	case ACTION_WALK_NORTH_END:
		action = ACTION_NONE;
		break;

	case ACTION_WALK_SOUTH_RIGHT:
	case ACTION_WALK_SOUTH_LEFT:
	case ACTION_WALK_SOUTH_END:
	case ACTION_WALK_EAST_RIGHT:
	case ACTION_WALK_EAST_LEFT:
	case ACTION_WALK_EAST_END:
	case ACTION_WALK_WEST_RIGHT:
	case ACTION_WALK_WEST_LEFT:
	case ACTION_WALK_WEST_END:
	default:
		return;
	}

	update_sprite(sprite_position*SPRITE_LENGHT_BYTES);
}
