/*
 * GameCharacter.cpp
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#include "GameCharacter.h"
#include "timming.h"

#include "util.h"


GameCharacter::GameCharacter(u8 *charset, size_t step_len_pixels, int x, int y):
VisualElement(charset, m_Pos_absolute),
m_Pos_absolute(x, y),
m_Pos_relative(0, 0),
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
	case ACTION_WALK_SOUTH_RIGHT:
	case ACTION_WALK_EAST_RIGHT:
	case ACTION_WALK_WEST_RIGHT:
		this->move(action);
		break;
	case ACTION_WALK_NORTH_LEFT:
	case ACTION_WALK_SOUTH_LEFT:
	case ACTION_WALK_EAST_LEFT:
	case ACTION_WALK_WEST_LEFT:
		if (interaction == 3) {
			this->move(action);
		}
		break;
	case ACTION_WALK_NORTH_RIGHT2:
	case ACTION_WALK_SOUTH_RIGHT2:
	case ACTION_WALK_EAST_RIGHT2:
	case ACTION_WALK_WEST_RIGHT2:
		if (interaction == 6) {
			this->move(action);
		}
		break;
	case ACTION_WALK_NORTH_END:
	case ACTION_WALK_SOUTH_END:
	case ACTION_WALK_EAST_END:
	case ACTION_WALK_WEST_END:
		this->move(action);
		break;

	case ACTION_NONE:
		this->move(action);
		break;
	default:
		break;
	}

	//if(action != ACTION_NONE) debug("action: %d; iteraction: %d", action, interaction);
}

/*************************************************************************************************/

void GameCharacter::move(en_char_action& action)
{
	const size_t last_step_offset = 1;
	static sprite_character_positions previous_sprite_position = SPRITE_FACING_NONE;
	sprite_character_positions sprite_position = previous_sprite_position;

	switch(action) {

	case ACTION_WALK_NORTH_RIGHT:
	case ACTION_WALK_NORTH_RIGHT2:
		action++;
		this->move_background(0, -1*(m_StepLen_pixes+last_step_offset));
		sprite_position = SPRITE_FACING_NORTH_STEP_RIGHT;
		break;

	case ACTION_WALK_NORTH_LEFT:
		action++;
		this->move_background(0, -1*m_StepLen_pixes);
		sprite_position = SPRITE_FACING_NORTH_STEP_LEFT;
		break;

	case ACTION_WALK_SOUTH_RIGHT:
	case ACTION_WALK_SOUTH_RIGHT2:
		action++;
		this->move_background(0, m_StepLen_pixes+last_step_offset);
		sprite_position = SPRITE_FACING_SOUTH_STEP_RIGHT;
		break;

	case ACTION_WALK_SOUTH_LEFT:
		action++;
		this->move_background(0, m_StepLen_pixes);
		sprite_position = SPRITE_FACING_SOUTH_STEP_LEFT;
		break;

	case ACTION_WALK_EAST_RIGHT:
	case ACTION_WALK_EAST_RIGHT2:
		action++;
		this->move_background(m_StepLen_pixes+last_step_offset, 0);
		sprite_position = SPRITE_FACING_EAST_STEP_RIGHT;
		break;

	case ACTION_WALK_EAST_LEFT:
		action++;
		this->move_background(m_StepLen_pixes, 0);
		sprite_position = SPRITE_FACING_EAST_STEP_LEFT;
		break;

	case ACTION_WALK_WEST_RIGHT:
	case ACTION_WALK_WEST_RIGHT2:
		action++;
		this->move_background(-1*(m_StepLen_pixes+last_step_offset), 0);
		sprite_position = SPRITE_FACING_WEST_STEP_RIGHT;
		break;

	case ACTION_WALK_WEST_LEFT:
		action++;
		this->move_background(-1*m_StepLen_pixes, 0);
		sprite_position = SPRITE_FACING_WEST_STEP_LEFT;
		break;

	case ACTION_WALK_NORTH_END:
	case ACTION_WALK_SOUTH_END:
	case ACTION_WALK_EAST_END:
	case ACTION_WALK_WEST_END:
		action = ACTION_NONE;
	case ACTION_NONE:
		sprite_position = SPRITE_FACING_NONE;
		// TODO TODO TODO
	default:
		return;
	}

	if (sprite_position != SPRITE_FACING_NONE) {
		/* Previous state will be and ending state if sprite_prosition is none. */
		previous_sprite_position = sprite_position;
		update_sprite(sprite_position*SPRITE_LENGHT_BYTES);
	}
}


/*************************************************************************************************/
/* Private Functions.                                                                            */
/*************************************************************************************************/


void GameCharacter::move_background(const int x_pixels, const int y_pixels)
{
	/* If can't scroll the background will not update the character relative position. */
	if (m_MapProcessor->scroll_Background(x_pixels, y_pixels) != 0) {
		return;
	}

	m_Pos_relative.x += x_pixels;
	m_Pos_relative.y += y_pixels;

	debug("pos_rela: %d.%d", m_Pos_relative.x, m_Pos_relative.y);
}
