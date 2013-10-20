/*
 * GameObject.h
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include "VisualElement.h"
#include "CollisionElement.h"

class GameObject: protected VisualElement, public CollisionElement {
private:
	/**
	 *  Position of the object in the screen. VisualElement needs a position in pixels, but work
	 *  with it in 8px scale when it's possible.
	 */
	st_offset m_Pos_relative_px;

	//! Printable object identifier.
	std::string m_Name;

public:
	/**
	 * \brief Class constructor
	 * \parameter rect The collision rectangle for action and moving.
	 * \parameter sprite The sprite set of the object.
	 * \parameter x_8px Horizontal relative position of the object.
	 * \parameter y_8px Vertical relative position of the object.
	 * \parameter initial_sprite The initial sprite to be displayed.
	 */
	GameObject(st_rect rect,
			u8 *sprite,
			int x_8px, int y_8px,
			unsigned int initial_sprite=SPRITE_FACING_NONE,
			std::string name="<unamed>");

	/**
	 * \brief Get relative position in pixels attribute.
	 */
	st_offset get_Pos_relative_px(void)
	{
		return m_Pos_relative_px;
	}

	/**
	 * \brief Get object name identifier.
	 */
	std::string get_Name(void)
	{
		return m_Name;
	}
};


#endif /* GAMEOBJECT_H_ */
