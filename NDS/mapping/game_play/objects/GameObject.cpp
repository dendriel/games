/*
 * GameObject.cpp
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#include "GameObject.h"
#include "util.h"

using namespace std;

/*************************************************************************************************/

GameObject::GameObject(
		st_rect rect,
		u8 *sprite,
		int x_8px, int y_8px,
		long type,
		unsigned int initial_sprite,
		std::string name,
		bool display,
		bool blockable,
		bool stackable):
VisualElement(&m_Pos_relative_px, sprite, display),
CollisionElement(rect, rect),	/* Action rectangle will no be used. */
m_Pos_relative_px(TILE_8PX_TO_PX(x_8px), TILE_8PX_TO_PX(y_8px)),
m_Name(name),
m_Id(GameObject::generate_id()),
m_Type(type),
m_Stackable(stackable),
m_Blockable(blockable)
{
	update_sprite(initial_sprite*SPRITE_LENGHT_BYTES);
	update_position();
}

GameObject::~GameObject(void)
{
	for (size_t i = 0; i < m_Triggers_list.size(); i++) {
		delete m_Triggers_list[i];
	}

	m_Triggers_list.clear();

	debug("Obj: %s destroyed.", this->get_Name().c_str());
}

/*************************************************************************************************/

bool GameObject::get_reaction(en_action action, Trigger * &trigger)
{
	for (vector<Trigger *>::iterator iter = m_Triggers_list.begin();
			iter != m_Triggers_list.end(); ++iter) {
		Trigger *curr = (*iter);

		if (curr->get_Enabled() != true) {
			continue;
		}

		if (action != curr->get_Action()) {
			continue;
		}

		// If there is charges.
		if (curr->get_Charges() > 0) {
			curr->decrement_Charges();
			trigger = curr;
			return true;
		}
		// Not chargeable.
		else if (curr->get_Charges() == -1) {
			trigger = curr;
			return true;
		}
		// No more charges.
		else {
			return false;
		}
	}
	// Trigger doesn't exist.
	return false;
}

/*************************************************************************************************/

void GameObject::disable_All_trigger(const en_action& reaction)
{
	// No reactions to disable.
	if (reaction == ACTION_NONE) {
		return;
	}

	for (vector<Trigger *>::iterator iter = m_Triggers_list.begin();
			iter != m_Triggers_list.end(); ++iter) {
		Trigger *curr = (*iter);

		if (reaction != curr->get_Action()) {
			continue;
		}

		curr->disable();
	}
}

