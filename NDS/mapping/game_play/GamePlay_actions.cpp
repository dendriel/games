/*
 * GamePlay_actions.cpp
 *
 *  Created on: 25/10/2013
 *      Author: marta
 */

#include "GamePlay.h"
#include <vector>
#include <cassert>

using namespace std;

/**
 * Created this module just to clearly divide some types of functions of the Game Play .
 */

/*************************************************************************************************/

void GamePlay::execute_queued_reactions(void)
{
	//debug("size: %d", m_ActionsQueue.size());
	while(m_ActionsQueue.size() > 0) {

		st_trigger& trigger = m_ActionsQueue.front();

		this->execute_action(trigger.reaction, &trigger);

		m_ActionsQueue.pop();
		debug("Pop %d reaction.", trigger.reaction);
	}
}

/*************************************************************************************************/

void GamePlay::execute_action(en_action& action, st_trigger *trigger)
{
	m_Character->update_actions_cooldown();

	switch(action) {

	case ACTION_TOUCH:
		this->touch_action();
	break;

	case ACTION_GIVE_OBJECT:
		assert(trigger != NULL);

		this->give_object_action(trigger->gen_id);
		break;

	/* Walk actions. */
	case ACTION_WALK_NORTH:
	case ACTION_WALK_SOUTH:
	case ACTION_WALK_EAST:
	case ACTION_WALK_WEST:
	case ACTION_NONE:
		m_Character->move(action);
		break;
	default:
		debug("Untreated action received.");
		break;
	}
}

/*************************************************************************************************/
/* Declare touching action. */
static bool check_touch_points(st_offset touching[], vector<GameObject *> *objects_list, st_trigger& trigger_data);
static bool check_touched_object(st_offset touching, st_rect area);

void GamePlay::touch_action(void)
{
	/* Check cool down. */
	if (m_Character->get_action_touch_cooldown() > 0) {
		//debug("cool down: %d", m_Character->get_action_touch_cooldown());
		return;
	}

	st_trigger trigger_data;
	st_offset touching[2];

	memset(touching, 0 , sizeof(touching));

	m_Character->get_touch_position(touching);

	if (check_touch_points(touching, m_Scenery->get_ObjectsList(), trigger_data) == true) {
		m_ActionsQueue.push(trigger_data);
		debug("Push %d reaction.", trigger_data.reaction);
	}

	/* Update cool down. */
	m_Character->set_action_touch_cooldown();
}

/**
 * \brief Touch items on the scenery.
 * \parameter touching The touching points to be verified.
 * \parameter objects_list List of objects in the scenery to check.
 * \return true if touched and filled the trigger parameter; false otherwise.
 */
static bool check_touch_points(st_offset touching[], vector<GameObject *> *objects_list, st_trigger& trigger_data)
{
	//debug("pa: %d,%d; pb: %d,%d", touching[0].x, touching[0].y, touching[1].x, touching[1].y);

	for (std::vector<GameObject *>::iterator iter = objects_list->begin();
			iter != objects_list->end(); ++ iter) {
		GameObject *object = *iter;
		st_rect relative_coor;

		relative_coor.pos.x = object->get_CollRect().pos.x + object->get_Pos_relative_px().x;
		relative_coor.pos.y = object->get_CollRect().pos.y + object->get_Pos_relative_px().y;
		relative_coor.w = relative_coor.pos.x + object->get_CollRect().w;
		relative_coor.h = relative_coor.pos.y + object->get_CollRect().h;

		// Check p1 and p2.
		if ((check_touched_object(touching[0], relative_coor) != true) &&
				(check_touched_object(touching[1], relative_coor) != true)) {
			// None of these points are touching anything.
			continue;
		}

		//debug("Touched object %s id: %ld!", object->get_Name().c_str(), object->get_Type());


		debug("obj: %s", object->get_Name().c_str());


		if (object->get_reaction(ACTION_TOUCH, trigger_data) != true) {
			// Return if there is no reaction.
			return false;
		}

		debug("Reaction: %d", trigger_data.reaction);
		return true;
	}

	return false;
}

/**
 * \brief Verify if the point is touching the area.
 * \parameter touching The touching point.
 * \parameter area The area to verify.
 * \return true if the area is being touched; false otherwise.
 */
static bool check_touched_object(st_offset touching, st_rect area)
{
	//debug("area: %d,%d; %d,%d", area.pos.x, area.pos.y, area.w, area.h);

	if (touching.x >= area.pos.x && touching.y >= area.pos.y &&
			touching.x <= static_cast<int>(area.w) && touching.y <= static_cast<int>(area.h)) {
		return true;
	}

	return false;
}

/*************************************************************************************************/

void GamePlay::give_object_action(const long& obj_id)
{
	GameObject *object = m_Scenery->get_Object(obj_id);

	/* If the object was not found, do nothing. If there is more lists that the object can be in,
	 * add here and keep searching before returning.
	 */
	if (object == NULL) {
		return;
	}

	// Add the item to the character.
	if (m_Character->add_Object(object) != true) {
		debug("no more space.");
		// error message here!
		return;
	}

	// The object was taken. Now it is in the inventory. TODO: update the inventory window.
	// Set object visibility.
	object->set_Visibility(false);

	// Remove duplicated references.
	m_Scenery->del_Object(obj_id);
}

/*************************************************************************************************/
