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

GameObject::GameObject(st_rect rect, u8 *sprite, int x_8px, int y_8px, long type, unsigned int initial_sprite, std::string name, bool display):
VisualElement(&m_Pos_relative_px, sprite, display),
CollisionElement(rect, rect),	/* Action rectangle will no be used. */
m_Pos_relative_px(TILE_8PX_TO_PX(x_8px), TILE_8PX_TO_PX(y_8px)),
m_Name(name),
m_Id(GameObject::generate_id()),
m_Type(type)
{
	update_sprite(initial_sprite*SPRITE_LENGHT_BYTES);
	update_position();
}

/*************************************************************************************************/


bool GameObject::get_reaction(en_action action, st_trigger& trigger)
{
	for (vector<st_trigger>::iterator iter = m_Triggers_list.begin();
			iter != m_Triggers_list.end(); ++iter) {

		debug("act %d != iter->trigger: %d ?", action, iter->trigger);
		if (action != iter->trigger) {
			debug("continue.");
			continue;
		}

		// If there is charges.
		if (iter->charges > 0) {
			iter->charges--;
			trigger = *iter;
			return true;
		}
		// Not chargeable.
		else if (iter->charges == -1) {
			trigger = *iter;
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

