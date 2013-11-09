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


GameCharacter::GameCharacter(st_rect rect, u8 *charset, int x_px, int y_px):
VisualElement(&m_Pos_absolute_px, charset),
CollisionElement(rect, rect), /* Use the normal collision rectangle as the action collision rectangle. */
m_Pos_relative_8px(PIXEL_TO_TILE_8PX(x_px), PIXEL_TO_TILE_8PX(y_px)),
m_Pos_absolute_px(x_px, y_px),
m_Facing(W_DOWN),
m_ActionMove_cooldown(0),
m_ActionTouch_cooldown(0),
m_ActionTakeDamage_cooldown(0)
{
	this->set_sprite(SPRITE_FACING_SOUTH_STOPPED);
	debug("Initial relative pos: %d,%d", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),
			TILE_8PX_TO_32PX(m_Pos_relative_8px.y));
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

void GameCharacter::update_actions_cooldown(void)
{
	//TODO: could build a constructor to auto check if cooldown > 0
	if (m_ActionMove_cooldown > 0) {
		m_ActionMove_cooldown--;
	}

	if (m_ActionTouch_cooldown > 0) {
		m_ActionTouch_cooldown--;
	}

	if (m_ActionTakeDamage_cooldown > 0) {
		m_ActionTakeDamage_cooldown--;
	}
}
