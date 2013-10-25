/*
 * Inventory.cpp
 *
 *  Created on: 24/10/2013
 *      Author: vitor
 */

#include "Inventory.h"
#include "util.h"

/*************************************************************************************************/

Inventory::Inventory(const size_t slot_max):
	m_Slot_list(slot_max)
{}

Inventory::~Inventory(void)
{

}

/*************************************************************************************************/

bool Inventory::add_object(GameObject *object)
{
	// iterate over inventory slots.
	for (vector<st_inventory_slot>::iterator slot = this->m_Slot_list.begin();
			slot != this->m_Slot_list.end(); ++slot) {

		GameObject *slot_item = slot->objects_list[0];

		// If the object type has already in the inventory.
		if (slot_item->get_Type() == object->get_Type()) {
			// If there is space in the stack.
			if (slot->stackable &&
					(slot->objects_list.size() < INVENTORY_DEFAULT_SLOT_SIZE)) {

				slot->objects_list.push_back(object);
				debug("Add stack obj: %s", object->get_Name().c_str());
				return true;
			}
			// The stack is full.
			else {
				return false;
			}
		}
	}

	// find a free slot and add the object. //TODO: i don't really like to have to iterate the slot's vector 2 times.. find a better solution.
	for (vector<st_inventory_slot>::iterator slot = this->m_Slot_list.begin();
			slot != this->m_Slot_list.end(); ++slot) {

		// If slot is free.
		if (slot->objects_list.size() == 0) {
			slot->objects_list.push_back(object);
			debug("Add new obj: %s", object->get_Name().c_str());
			return true;
		}
	}

	return false;
}

/*************************************************************************************************/
