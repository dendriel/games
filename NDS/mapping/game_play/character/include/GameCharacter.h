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
#include "GameMapProcessor.h"
#include "Inventory.h"
#include "game_actions.h"

//testing purpose
#include "objects.h"
#include <iostream>

class GameCharacter: private VisualElement, CollisionElement {
public:
	st_offset m_Pos_relative_8px;	//!< Position of the character in the screen (not the scenery. Relative position).

private:
	st_offset m_Pos_absolute_px;	//!< Position of the character in the screen (not the scenery. Absolute position in Pixels).
	en_facing m_Facing;				//!< Facing direction.
	GameMapProcessor *m_MapProcessor;
	Inventory m_Inventory;

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
	 * \brief Add the map processor reference.
	 */
	void set_map_processor(GameMapProcessor& processor);

	/**
	 * \brief Move the character.
	 * \parameter action Contains information about where to move. Also will be change to the next action.
	 * \parameter direction Which direction to move.
	 */
	void move(en_action& action);
	void move(const int x, const int y);

	/**
	 * \brief Set character relative position. Also move the map.
	 */
	void set_relative_pos_32px(const int x, const int y);

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
	unsigned short get_action_touch_cooldown(void);

	/**
	 * \brief Update touch action cool down to full value.
	 */
	void set_action_touch_cooldown(void);

	/**
	 * \brief Add item to inventory.
	 */
	bool add_object(GameObject *object)
	{
		return m_Inventory.add_Object(object);
	}

	void delete_object(const long& id)
	{
		m_Inventory.delete_object(id);
	}

	/**
	 * \brief Check if the character have the object in the inventory.
	 * \parameter if The id of the object to be verified.
	 * \return true if the object was found; false otherwise.
	 */
	bool check_object(const long& id)
	{
		return m_Inventory.check_object(id);
	}

	// Testing function.
	void get_Inventory(void)
	{
		std::vector<st_inventory_slot> slot_list = m_Inventory.get_Slot_list();

		for (std::vector<st_inventory_slot>::iterator slot = slot_list.begin(); slot != slot_list.end(); ++slot) {
			std::cout << "slot: ";
			for (std::vector<GameObject *>::iterator obj = slot->objects_list.begin(); obj != slot->objects_list.end(); ++obj) {
				std::cout << ((*obj)->get_Name()) << " (" << slot->objects_list.size() << ")";
				break; // just the first.
			}
			std::cout << std::endl;
		}
	}

private:
	/**
	 * \brief Move the map and update character relative position.
	 * \parameter x Character horizontal relative position.
	 * \parameter y Character vertical relative position.
	 */
	void move_background_8px(const int x, const int y);

};

// Overload game character to access the inventory overload.
inline GameCharacter& operator<<(GameCharacter& character, GameObject *object)
{
	(void) character.add_object(object);
	return character;
}

#endif /* GAMECHARACTER_H_ */
