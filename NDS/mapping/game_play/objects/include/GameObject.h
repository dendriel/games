/*
 * GameObject.h
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <string>
#include "VisualElement.h"
#include "CollisionElement.h"
#include "Trigger.h"
#include "game_actions.h"


class GameObject: protected VisualElement, public CollisionElement {
private:
	/**
	 *  Position of the object in the screen. VisualElement needs a position in pixels, but you may
	 *  work with in 8px scale whenever is possible.
	 */
	st_offset m_Pos_relative_px;
	std::string m_Name;						//!< Printable object identifier.
	long m_Id;								//!< Current object ID.
	long m_Type;							//!< Object unique ID.
	bool m_Stackable;						//!< If in an inventory, is able to be stacked.
	bool m_Blockable;						//!< If the character will be blocked when running into the object.
	std::vector<Trigger *> m_Triggers_list;//!< Map reactions of the object to possible actions.
	static long s_Object_ids;				//!< IDs for distribute to objects.

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
			bool display=true,
			bool blockable=false,
			bool stackable=false);

	/**
	 * \brief Class destructor.
	 */
	~GameObject(void);


	/**
	 * \brief Checks if there is an reaction registered for the given action.
	 * \parameter action The action to be searched.
	 * \return If there is a trigger for the action, decrement the trigger charges, fill the trigger
	 *  parameter and return true; Otherwise, just return false.
	 */
	bool get_reaction(en_action action, Trigger* &trigger);

	/**
	 * \brief Get relative position in pixels attribute.
	 */
	inline st_offset get_Pos_relative_px(void)
	{
		return m_Pos_relative_px;
	}

	/**
	 * \brief Get the object name identifier.
	 */
	inline std::string get_Name(void)
	{
		return m_Name;
	}

	/**
	 * \brief Return object current ID.
	 */
	inline long get_Id(void)
	{
		return m_Id;
	}

	/**
	 * \brief Return object type.
	 */
	inline long get_Type(void)
	{
		return m_Type;
	}

	/**
	 * \brief Add a trigger for the object.
	 */
	inline void set_Trigger(Trigger *trigger)
	{
		m_Triggers_list.push_back(trigger);
	}

	/**
	 * \brief Set visual element visibility.
	 * \parameter display Display (true) or not (false) the element in the screen.
	 */
	inline void set_Visibility(const bool display)
	{
		set_Display(display);
	}

	/**
	 * \brief Return the stack able property.
	 */
	inline bool get_Stackable(void)
	{
		return m_Stackable;
	}

	/**
	 * \brief Return the block able property.
	 */
	inline bool get_Blockable(void)
	{
		return m_Blockable;
	}

	/**
	 * \brief Change object displaying sprite.
	 */
	inline void set_sprite(const int& sprite)
	{
		update_sprite(sprite*SPRITE_LENGHT_BYTES);
		update_position();
	}

	/**
	 * \brief Disable all triggers that have the given reaction;
	 * \parameter reaction Trigger type to be disabled.
	 */
	void disable_All_trigger(const en_action& reaction);

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

//! Objects types Types. *Don't start at zero as this is a default value for "no value".
enum {
	GAMEOBJECT_TYPE_0 = 100, // Torch
	GAMEOBJECT_TYPE_1,		 // Lever
	GAMEOBJECT_TYPE_2,		 // Lever Holder
};

#endif /* GAMEOBJECT_H_ */
