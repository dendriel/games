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

#define ACTION_MOVE_COOLDOWN_CYCLES 6 //!< *16ms
#define ACTION_TOUCH_COOLDOWN_CYCLES 10


GameCharacter::GameCharacter(st_rect rect, u8 *charset, int x_px, int y_px):
VisualElement(&m_Pos_absolute_px, charset),
CollisionElement(rect, rect), /* Use the normal collision rectangle as the action collision rectangle. */
m_Pos_relative_8px(PIXEL_TO_TILE_8PX(x_px), PIXEL_TO_TILE_8PX(y_px)),
m_Pos_absolute_px(x_px, y_px),
m_Facing(W_DOWN),
m_MapProcessor(0),
m_ActionMove_cooldown(0),
m_ActionTouch_cooldown(0)
{
	update_sprite(SPRITE_FACING_SOUTH_STOPPED*SPRITE_LENGHT_BYTES);
	update_position();

	debug("Initial relative pos: %d,%d", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),
			TILE_8PX_TO_32PX(m_Pos_relative_8px.y));
}

/*************************************************************************************************/

void GameCharacter::set_map_processor(GameMapProcessor& processor)
{
	m_MapProcessor = &processor;
}

/*************************************************************************************************/

void GameCharacter::move(en_action& action)
{
	/* If still in cool down. */
	if (m_ActionMove_cooldown > 0) {
		return;
	}

	static bool is_right_step = false;
	static en_action previous_action = ACTION_NONE;

	en_sprite_character_positions sprite_position;

	switch(action) {
		case ACTION_WALK_NORTH:
			this->move_background_8px(0, -1);
			sprite_position =
					(is_right_step)? SPRITE_FACING_NORTH_STEP_RIGHT : SPRITE_FACING_NORTH_STEP_LEFT;
			m_Facing = W_UP;
			break;

		case ACTION_WALK_SOUTH:
			this->move_background_8px(0, 1);
			sprite_position =
					(is_right_step)? SPRITE_FACING_SOUTH_STEP_RIGHT : SPRITE_FACING_SOUTH_STEP_LEFT;
			m_Facing = W_DOWN;
			break;

		case ACTION_WALK_EAST:
			this->move_background_8px(1, 0);
			sprite_position =
					(is_right_step)? SPRITE_FACING_EAST_STEP_RIGHT : SPRITE_FACING_EAST_STEP_LEFT;
			m_Facing = W_RIGHT;
			break;

		case ACTION_WALK_WEST:
			this->move_background_8px(-1, 0);
			sprite_position =
					(is_right_step)? SPRITE_FACING_WEST_STEP_RIGHT : SPRITE_FACING_WEST_STEP_LEFT;
			m_Facing = W_LEFT;
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

	update_sprite(sprite_position*SPRITE_LENGHT_BYTES);

	update_position();

	/* Updating the cool down here will add a delay to starting moving. */
	m_ActionMove_cooldown = ACTION_MOVE_COOLDOWN_CYCLES;
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

	//debug("Moved to: %d,%d (%d,%d)",x,y, m_Pos_relative_8px.x, m_Pos_relative_8px.y);

	m_MapProcessor->move_map_32px(move_x_32px, move_y_32px);
}

/*************************************************************************************************/

#define TOUCH_RANGE 4
#define HALF_TOUCH_RANGE TOUCH_RANGE/2

void GameCharacter::get_touch_position(st_offset *touching)
{
	// TODO: verify and continue to build touch action.
	if (touching == NULL) {
		return;
	}

	st_offset *pa = &touching[0];
	st_offset *pb = &touching[1];

	unsigned int x  = m_ActionCollRect.pos.x + TILE_8PX_TO_PX(m_Pos_relative_8px.x);
	unsigned int y  = m_ActionCollRect.pos.y + TILE_8PX_TO_PX(m_Pos_relative_8px.y);

	/* Do the calculations here. */
	unsigned short xp1, xp2, xp3, xp4;
	unsigned short yp1, yp2, yp3, yp4;

	xp1 = x - TOUCH_RANGE;
	xp2 = (x + m_ActionCollRect.w/2) - HALF_TOUCH_RANGE;
	xp3 = (x + m_ActionCollRect.w/2) + HALF_TOUCH_RANGE;
	xp4 = x + m_ActionCollRect.w + TOUCH_RANGE;

	yp1 = y - TOUCH_RANGE;
	yp2 = (y + m_ActionCollRect.h/2) - HALF_TOUCH_RANGE;
	yp3 = (y + m_ActionCollRect.h/2) + HALF_TOUCH_RANGE;
	yp4 = y + m_ActionCollRect.h + TOUCH_RANGE;

	switch(m_Facing) {

	case W_UP:
		pa->x = xp2; pa->y = yp1;
		pb->x = xp3; pb->y = yp1;
		break;

	case W_DOWN:
		pa->x = xp2; pa->y = yp4;
		pb->x = xp3; pb->y = yp4;
		break;

	case W_LEFT:
		pa->x = xp1; pa->y = yp2;
		pb->x = xp1; pb->y = yp3;

	break;

	case W_RIGHT:
		pa->x = xp4; pa->y = yp2;
		pb->x = xp4; pb->y = yp3;
	break;

	default:
		pa->x = 0; pa->y = 0;
		pb->x = 0; pb->y = 0;
		debug("Invalid character facing direction.");
		break;
	}

}

/*************************************************************************************************/
/* Private Functions.                                                                            */
/*************************************************************************************************/

void GameCharacter::move_background_8px(const int x, const int y)
{
	int relative_pos_x_px = TILE_8PX_TO_PX(m_Pos_relative_8px.x + x);
	int relative_pos_y_px = TILE_8PX_TO_PX(m_Pos_relative_8px.y + y);

	st_rect collision_element(m_CollRect.pos.x + relative_pos_x_px,
								m_CollRect.pos.y + relative_pos_y_px,
								m_CollRect.w, m_CollRect.h);

	if (m_MapProcessor->check_static_collision(collision_element) == 1) {
		return;
	}

	/* If can't scroll the background will not update the character relative position. */
	if (m_MapProcessor->move_map_8px(x, 0) == 0) {
		m_Pos_relative_8px.x+=x;
	}

	if (m_MapProcessor->move_map_8px(0, y) == 0) {
		m_Pos_relative_8px.y+=y;
	}

	//debug(" posRela: %d,%d (%d,%d)", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),TILE_8PX_TO_32PX(m_Pos_relative_8px.y), m_Pos_relative_8px.x, m_Pos_relative_8px.y);
}

/*************************************************************************************************/

void GameCharacter::update_actions_cooldown(void)
{
	//TODO: could build a constructor to auto check if cooldown > 0
	if (m_ActionMove_cooldown > 0) {
		m_ActionMove_cooldown--;
	}

	if (m_ActionTouch_cooldown > 0) {
		m_ActionTouch_cooldown--;
	}
}

/*************************************************************************************************/

unsigned short GameCharacter::get_action_touch_cooldown(void)
{
	return m_ActionTouch_cooldown;
}

/*************************************************************************************************/

void GameCharacter::set_action_touch_cooldown(void)
{
	m_ActionTouch_cooldown = ACTION_TOUCH_COOLDOWN_CYCLES;
}

