/*
 * GameCharacter.cpp
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#include "GameCharacter.h"
#include <assert.h>
#include "timming.h"

#include "util.h"

#define ACTION_MOVE_COOLDOWN_CYCLES 6	//! *16ms


GameCharacter::GameCharacter(u8 *charset, int x_px, int y_px):
VisualElement(charset, m_Pos_absolute_px),
m_Pos_absolute_px(x_px, y_px),
m_Pos_relative_8px(PIXEL_TO_TILE_8PX(x_px), PIXEL_TO_TILE_8PX(y_px)),
m_Facing(W_DOWN),
m_MapProcessor(0),
m_ActionMove_cooldown(0)
{
	update_sprite(0);
	debug("Initial relative pos: %d,%d", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),
			TILE_8PX_TO_32PX(m_Pos_relative_8px.y));
}

/*************************************************************************************************/

void GameCharacter::set_map_processor(GameMapProcessor& processor)
{
	m_MapProcessor = &processor;
}

/*************************************************************************************************/

void GameCharacter::execute_action(en_char_action& action)
{
	this->update_actions_cooldown();

	switch(action) {

	/* Walk actions. */
	case ACTION_WALK_NORTH:
	case ACTION_WALK_SOUTH:
	case ACTION_WALK_EAST:
	case ACTION_WALK_WEST:
	case ACTION_NONE:
		this->move(action);
		break;
	default:
		debug("Untreated action received.");
		break;
	}
}

/*************************************************************************************************/

void GameCharacter::move(en_char_action& action)
{
	/* If still in cool down. */
	if (m_ActionMove_cooldown > 0) {
		return;
	}

	static bool is_right_step = false;
	static en_char_action previous_action = ACTION_NONE;

	sprite_character_positions sprite_position;

	switch(action) {
		case ACTION_WALK_NORTH:
			this->move_background_8px(0, -1);
			sprite_position =
					(is_right_step)? SPRITE_FACING_NORTH_STEP_RIGHT : SPRITE_FACING_NORTH_STEP_LEFT;
			break;

		case ACTION_WALK_SOUTH:
			this->move_background_8px(0, 1);
			sprite_position =
					(is_right_step)? SPRITE_FACING_SOUTH_STEP_RIGHT : SPRITE_FACING_SOUTH_STEP_LEFT;
			break;

		case ACTION_WALK_EAST:
			this->move_background_8px(1, 0);
			sprite_position =
					(is_right_step)? SPRITE_FACING_EAST_STEP_RIGHT : SPRITE_FACING_EAST_STEP_LEFT;
			break;

		case ACTION_WALK_WEST:
			this->move_background_8px(-1, 0);
			sprite_position =
					(is_right_step)? SPRITE_FACING_WEST_STEP_RIGHT : SPRITE_FACING_WEST_STEP_LEFT;
			break;
		case ACTION_NONE:
			/* If was no previous action, sprite is already in standing position. */
			if (previous_action == ACTION_NONE) {
				return;
			}

			switch(previous_action) {
				case ACTION_WALK_NORTH: sprite_position = SPRITE_FACING_NORTH_STOPPED; break;
				case ACTION_WALK_SOUTH: sprite_position = SPRITE_FACING_SOUTH_STOPPED; break;
				case ACTION_WALK_EAST: sprite_position = SPRITE_FACING_EAST_STOPPED; break;
				case ACTION_WALK_WEST: sprite_position = SPRITE_FACING_WEST_STOPPED; break;
				default: assert(0); break; /* Something is really wrong. */
			}
			break;
		default:
			debug("Invalid walk action received.");
			return;
	}

	previous_action = action;
	is_right_step = !is_right_step;
	/* Updating the cool down here will add a delay to starting moving. */
	m_ActionMove_cooldown = ACTION_MOVE_COOLDOWN_CYCLES;

	update_sprite(sprite_position*SPRITE_LENGHT_BYTES);
}

void GameCharacter::set_relative_pos_32px(const int x, const int y)
{
	if ((x < SPRITE_SCREEN_CENTER_X_TILES) || (y < SPRITE_SCREEN_CENTER_Y_TILES)) {
		debug("Invalid character starting point.");
		assert(0);
		return;
	}

	const int move_x_32px = x - SPRITE_SCREEN_CENTER_X_TILES;
	const int move_y_32px = y - SPRITE_SCREEN_CENTER_Y_TILES;

	m_Pos_relative_8px.x += TILE_32PX_TO_8PX(move_x_32px);
	m_Pos_relative_8px.y += TILE_32PX_TO_8PX(move_y_32px);

	debug("Moved to: %d,%d (%d,%d)",x,y, m_Pos_relative_8px.x, m_Pos_relative_8px.y);

	m_MapProcessor->move_map_32px(move_x_32px, move_y_32px);
}

/*************************************************************************************************/
/* Private Functions.                                                                            */
/*************************************************************************************************/

void GameCharacter::move_background_8px(const int x, const int y)
{

	/* If can't scroll the background will not update the character relative position. */
	if (m_MapProcessor->move_map_8px(x, 0) == 0) {
		m_Pos_relative_8px.x+=x;
	}

	if (m_MapProcessor->move_map_8px(0, y) == 0) {
		m_Pos_relative_8px.y+=y;
	}

	debug(" posRela: %d,%d (%d,%d)", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),
			TILE_8PX_TO_32PX(m_Pos_relative_8px.y), m_Pos_relative_8px.x, m_Pos_relative_8px.y);
}

/*************************************************************************************************/

void GameCharacter::update_actions_cooldown(void)
{
	//TODO: could build a constructor to auto check if cooldown > 0
	if (m_ActionMove_cooldown > 0) {
		m_ActionMove_cooldown--;
	}
}
