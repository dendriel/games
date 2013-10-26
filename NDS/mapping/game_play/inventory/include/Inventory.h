/*
 * Inventory.h
 *
 *  Created on: 24/10/2013
 *      Author: vitor
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <vector>
#include "GameObject.h"

#include "util.h"

using namespace std;

//! Slots of the inventory.
typedef struct st_inventory_slot {
	vector<GameObject *> objects_list;	//!< Objects in this slot.
	bool stackable;						//!< If the item is stackable. The first item will set this property.

	st_inventory_slot(void):
		stackable(false)
		{};
} st_inventory_slot;

#define INVENTORY_DEFAULT_MAX_SLOTS 6
#define INVENTORY_DEFAULT_SLOT_SIZE 5

class Inventory {
private:
	vector<st_inventory_slot> m_Slot_list;	// Make slots list as queues.

public:
	/**
	 * \brief Class constructor.
	 * \parameter slot_max The slot quantity in the inventory.
	 */
	Inventory(const size_t slot_max=INVENTORY_DEFAULT_MAX_SLOTS);

	/**
	 * \brief Class destructor.
	 */
	~Inventory(void);

	/**
	 * \brief Add object into inventory.
	 * \parameter object The item to be added.
	 * \return true: if the object was added; false: if there is no more space in the inventory.
	 * \note Behavior: Will stack the objects with same type in the same slot until limit is
	 * reached. Can't have two stacks of the same object.
	 */
	bool add_Object(GameObject *object);

	vector<st_inventory_slot> get_Slot_list(void)
	{
		return this->m_Slot_list;
	}
};

// Overload Inventory so we can just "drop" items in it.
inline Inventory& operator<<(Inventory& inventory, GameObject *object)
{
	(void) inventory.add_Object(object);
	return inventory;
}

#endif /* INVENTORY_H_ */
