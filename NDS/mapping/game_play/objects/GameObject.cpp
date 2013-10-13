/*
 * GameObject.cpp
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#include "GameObject.h"
#include "util.h"


GameObject::GameObject(st_rect rect, u8 *sprite, int x_8px, int y_8px, unsigned int initial_sprite):
VisualElement(&m_Pos_relative_px, sprite),
CollisionElement(rect, rect),	/* Action rectangle will no be used. */
m_Pos_relative_px(TILE_8PX_TO_PX(x_8px), TILE_8PX_TO_PX(y_8px))
{
	update_sprite(initial_sprite*SPRITE_LENGHT_BYTES);
	update_position();
}
