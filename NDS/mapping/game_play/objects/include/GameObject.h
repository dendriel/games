/*
 * GameObject.h
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "VisualElement.h"
#include "CollisionElement.h"

class GameObject: protected VisualElement, CollisionElement {
private:
	/**
	 *  Position of the object in the screen. VisualElement needs a position in pixels, but work
	 *  with it in 8px scale when it's possible.
	 */
	st_offset m_Pos_relative_px;
public:
	/**
	 * \brief Class constructor
	 * \parameter rect The collision rectangle for action and moving.
	 * \parameter sprite The sprite set of the object.
	 * \parameter x_8px Horizontal relative position of the object.
	 * \parameter y_8px Vertical relative position of the object.
	 * \parameter initial_sprite The initial sprite to be displayed.
	 */
	GameObject(st_rect rect, u8 *sprite, int x_8px, int y_8px, unsigned int initial_sprite=SPRITE_FACING_NONE);
};


#endif /* GAMEOBJECT_H_ */
