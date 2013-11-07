/*
 * GameCharacter.h
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include "VisualElement.h"
#include "CollisionElement.h"
#include "StatusElement.h"
#include "GameMapProcessor.h"
#include "Inventory.h"
#include "game_actions.h"

//testing purpose
#include "objects.h"
#include <iostream>

class GameCharacter: private VisualElement, CollisionElement, StatusElement {
public:
	st_offset m_Pos_relative_8px;	//!< Position of the character in the screen (not the scenery. Relative position).

private:
	st_offset m_Pos_absolute_px;	//!< Position of the character in the screen (not the scenery. Absolute position in Pixels).
	en_facing m_Facing;				//!< Facing direction.
	Inventory m_Inventory;			//!< Character objects inventory.
	/* Actions cool down. */
	unsigned short m_ActionMove_cooldown;	//!< Cool down before moving action.
	unsigned short m_ActionTouch_cooldown;	//!< Cool down before touching action.

public:
	/**
	 * \brief Class constructor.
	 * \parameter rect Collision rectangle of the character (also used as action collision rectangle).
	 * \parameter charset Character charset data.
	 * \parameter x_px Character horizontal absolute position.
	 * \parameter y_px Character vertical absolute position.
	 */
	GameCharacter(st_rect rect, u8 *charset = 0, int x_px = 0, int y_px = 0);

	/**
	 * \brief Update all actions cool down.
	 */
	void update_actions_cooldown(void);

	/**
	 * \brief Find where the character is touching.
	 * \brief touching A 2 rows array (output).
	 * \note Will fill the touching array with the touching points. See collisionElement class description.
	 */
	void get_touch_position(st_offset *touching);

	/**
	 * \brief Get action touch cool down.
	 */
	inline unsigned short get_action_touch_cooldown(void)
	{
		return m_ActionTouch_cooldown;
	}

	/**
	 * \brief Update touch action cool down to full value.
	 */
	inline void set_action_touch_cooldown(const unsigned int& cooldown_vsync_cycles)
	{
		m_ActionTouch_cooldown = cooldown_vsync_cycles;
	}

	/**
	 * \brief Return the cool down before moving again.
	 */
	inline unsigned short get_action_move_cooldown(void)
	{
		return m_ActionMove_cooldown;
	}

	/**
	 * \brief Update touch action cool down to full value.
	 */
	inline void set_action_move_cooldown(const unsigned int& cooldown_vsync_cycles)
	{
		m_ActionMove_cooldown = cooldown_vsync_cycles;
	}

	/**
	 * \brief Add item to inventory.
	 */
	inline bool add_object(GameObject *object)
	{
		return m_Inventory.add_Object(object);
	}

	/**
	 * \brief Delete item from inventory.
	 */
	inline void delete_object(const long& id)
	{
		m_Inventory.delete_object(id);
	}

	inline int get_relative_pos_x_8px(void)
	{
		return m_Pos_relative_8px.x;
	}

	/**
	 * \brief Increment the relative horizontal position (can be a negative increment).
	 */
	inline void add_relative_pos_x_8px(const int& offset)
	{
		m_Pos_relative_8px.x += offset;
	}

	inline int get_relative_pos_y_8px(void)
	{
		return m_Pos_relative_8px.y;
	}

	/**
	 * \brief Increment the relative vertical position (can be a negative increment).
	 */
	inline void add_relative_pos_y_8px(const int& offset)
	{
		m_Pos_relative_8px.y += offset;
	}

	/**
	 * \brief Get the character collision rectangle.
	 */
	inline st_rect get_collision_rect(void)
	{
		return get_CollRect();
	}

	/**
	 * \brief Check if the character have the object in the inventory.
	 * \parameter if The id of the object to be verified.
	 * \return true if the object was found; false otherwise.
	 */
	inline bool check_object(const long& id)
	{
		return m_Inventory.check_object(id);
	}

	/**
	 * \brief Set where to the character is looking.
	 */
	inline void set_facing_direction(const en_facing& direction)
	{
		m_Facing = direction;
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
	 * \brief Remove health points.
	 * \parameter amount How much of health points to be removed.
	 */
	inline void remove_hp(const unsigned short& amount)
	{
		dec_health_points(amount);
	}

	// Testing function.
	void get_Inventory(void)
	{
		const size_t cooldown_size = 10;
		static unsigned int cooldown = cooldown_size;

		if (cooldown > 0) {
			cooldown--;
			return;
		}

		std::vector<st_inventory_slot> slot_list = m_Inventory.get_Slot_list();

		for (std::vector<st_inventory_slot>::iterator slot = slot_list.begin(); slot != slot_list.end(); ++slot) {
			std::cout << "slot: ";
			for (std::vector<GameObject *>::iterator obj = slot->objects_list.begin(); obj != slot->objects_list.end(); ++obj) {
				std::cout << ((*obj)->get_Name()) << " (" << slot->objects_list.size() << ")";
				break; // just the first.
			}
			std::cout << std::endl;
		}

		std::cout << get_health_points() << std::endl;

		cooldown = cooldown_size;
	}
};

// Overload game character to access the inventory overload.
inline GameCharacter& operator<<(GameCharacter& character, GameObject *object)
{
	(void) character.add_object(object);
	return character;
}

#endif /* GAMECHARACTER_H_ */
