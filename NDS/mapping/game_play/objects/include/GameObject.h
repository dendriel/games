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

	//! Current object ID.
	long m_Id;

	//! Object unique ID.
	long m_Type;

	//! IDs for distribute to objects.
	static long s_Object_ids;

public:
	/**
	 * \brief Class constructor
	 * \parameter rect The collision rectangle for action and moving.
	 * \parameter sprite The sprite set of the object.
	 * \parameter x_8px Horizontal relative position of the object.
	 * \parameter y_8px Vertical relative position of the object.
	 * \parameter type The unique identifier of the object.
	 * \parameter initial_sprite The initial sprite to be displayed.
	 * \parameter name Visual identifier of the object.
	 * \parameter display Display or hide the visual element in the screen.
	 */
	GameObject(st_rect rect,
			u8 *sprite,
			int x_8px, int y_8px,
			long type,
			unsigned int initial_sprite=SPRITE_FACING_NONE,
			std::string name="<unamed>",
			bool display=true);

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

	/**
	 * \brief Return object current ID.
	 */
	long get_Id(void)
	{
		return m_Id;
	}

	/**
	 * \brief Return object type.
	 */
	long get_Type(void)
	{
		return m_Type;
	}

private:
/*************************************************************************************************/
/* Static Functions                                                                              */
/*************************************************************************************************/
	/**
	 * \brief Generate an ID for each item.
	 */
	static long generate_id(void)
	{
		return s_Object_ids++;
	}
};

//! Objects types Types. *Don't start at zero as this is a default value for no value.
enum {
	GAMEOBJECT_TYPE_0 = 100, // Torch
	GAMEOBJECT_TYPE_1,	 // Lever
};

#endif /* GAMEOBJECT_H_ */
