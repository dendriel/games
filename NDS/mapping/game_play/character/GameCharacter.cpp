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


GameCharacter::GameCharacter(u8 *charset, int x_px, int y_px):
VisualElement(charset, m_Pos_absolute_px),
m_Pos_absolute_px(x_px, y_px),
m_Pos_relative_8px(PIXEL_TO_TILE_8PX(x_px), PIXEL_TO_TILE_8PX(y_px)),
m_Facing(W_DOWN),
m_MapProcessor(0)
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
	case ACTION_WALK_NORTH_LEFT2:
	case ACTION_WALK_SOUTH_LEFT2:
	case ACTION_WALK_EAST_LEFT2:
	case ACTION_WALK_WEST_LEFT2:
		if (interaction == 9) {
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
}

/*************************************************************************************************/

void GameCharacter::move(en_char_action& action)
{
	static sprite_character_positions previous_sprite_position = SPRITE_FACING_NONE;
	sprite_character_positions sprite_position = previous_sprite_position;

	switch(action) {

	case ACTION_WALK_NORTH_RIGHT:
	case ACTION_WALK_NORTH_RIGHT2:
		action++;
		this->move_background_8px(0, -1);
		sprite_position = SPRITE_FACING_NORTH_STEP_RIGHT;
		break;

	case ACTION_WALK_NORTH_LEFT:
	case ACTION_WALK_NORTH_LEFT2:
		action++;
		this->move_background_8px(0, -1);
		sprite_position = SPRITE_FACING_NORTH_STEP_LEFT;
		break;

	case ACTION_WALK_SOUTH_RIGHT:
	case ACTION_WALK_SOUTH_RIGHT2:
		action++;
		this->move_background_8px(0, 1);
		sprite_position = SPRITE_FACING_SOUTH_STEP_RIGHT;
		break;

	case ACTION_WALK_SOUTH_LEFT:
	case ACTION_WALK_SOUTH_LEFT2:
		action++;
		this->move_background_8px(0, 1);
		sprite_position = SPRITE_FACING_SOUTH_STEP_LEFT;
		break;

	case ACTION_WALK_EAST_RIGHT:
	case ACTION_WALK_EAST_RIGHT2:
		action++;
		this->move_background_8px(1, 0);
		sprite_position = SPRITE_FACING_EAST_STEP_RIGHT;
		break;

	case ACTION_WALK_EAST_LEFT:
	case ACTION_WALK_EAST_LEFT2:
		action++;
		this->move_background_8px(1, 0);
		sprite_position = SPRITE_FACING_EAST_STEP_LEFT;
		break;

	case ACTION_WALK_WEST_RIGHT:
	case ACTION_WALK_WEST_RIGHT2:
		action++;
		this->move_background_8px(-1, 0);
		sprite_position = SPRITE_FACING_WEST_STEP_RIGHT;
		break;

	case ACTION_WALK_WEST_LEFT:
	case ACTION_WALK_WEST_LEFT2:
		action++;
		this->move_background_8px(-1, 0);
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

	debug("Moved to: %d,%d",x,y);

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

	//debug("pos_rela: %d,%d | %d,%d", TILE_8PX_TO_PX(m_Pos_relative_8px.x), TILE_8PX_TO_PX(m_Pos_relative_8px.y), TILE_8PX_TO_32PX(m_Pos_relative_8px.x), TILE_8PX_TO_32PX(m_Pos_relative_8px.y));
	//debug("posRela: %d,%d", m_Pos_relative_8px.x, m_Pos_relative_8px.y);
	debug(" posRela: %d,%d", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),
			TILE_8PX_TO_32PX(m_Pos_relative_8px.y));

}
