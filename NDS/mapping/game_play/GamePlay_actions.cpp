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

#define ACTION_MOVE_COOLDOWN_CYCLES 6 //!< *16ms
#define ACTION_TOUCH_COOLDOWN_CYCLES 10

/**
 * Created this module just to clearly divide some types of functions of the Game Play .
 */

/*************************************************************************************************/

void GamePlay::execute_queued_reactions(void)
{
	//debug("size: %d", m_ActionsQueue.size());
	while(m_ActionsQueue.size() > 0) {

		Trigger *trigger = m_ActionsQueue.front();

		//debug("Pop %d reaction.", trigger->get_Reaction());
		this->execute_action(trigger->get_Reaction(), trigger);

		m_ActionsQueue.pop();
	}
}

/*************************************************************************************************/

void GamePlay::execute_action(en_action action, Trigger *trigger)
{
	switch(action) {

	case ACTION_TOUCH:
		this->touch_action();
	break;

	case ACTION_GIVE_OBJECT:
		assert(trigger != NULL);

		this->give_object_action(trigger->get_Gen_id());
		break;

	case ACTION_CHECK_OBJECT:
		assert(trigger != NULL);
		this->check_for_object_action(trigger->get_Gen_id(), trigger->get_Next_reaction());
		break;

	case ACTION_REMOVE_OBJECT:
		assert(trigger != NULL);
		this->remove_object_action(trigger->get_Gen_id(), trigger->get_Next_reaction());
		break;

	case ACTION_CHANGE_SPRITE:
		assert(trigger != NULL);
		this->change_sprite_action(trigger->get_Gen_id(), trigger->get_Gen_pos(), trigger->get_Next_reaction());
		break;

	case ACTION_CHANGE_REACTION:
		assert(trigger != NULL);
		this->change_reaction_action(trigger->get_Gen_id(), static_cast<en_action>(trigger->get_Gen_pos()), trigger->get_Next_reaction());
		break;


	/* Walk actions (ACTION_NONE == stand the character). */
	case ACTION_WALK_NORTH:
	case ACTION_WALK_SOUTH:
	case ACTION_WALK_EAST:
	case ACTION_WALK_WEST:
	case ACTION_NONE:
		this->move_character_action(action);
		break;
	default:
		debug("Untreated action received. %d", action);
		break;
	}
}

/*************************************************************************************************/
/* Declare moving action. */
void GamePlay::move_character_action(en_action& direction)
{

	static bool is_right_step = false;
	static en_action previous_action = ACTION_NONE;
	int horizontal = 0;
	int vertical = 0;
	en_facing facing = W_DEFAULT;

	/* If still in cool down or in standing state. */
	if ((m_Character->get_action_move_cooldown() > 0) ||
		((direction == ACTION_NONE) && (previous_action == ACTION_NONE))) {
		return;
	}

	en_sprite_character_positions sprite_position;

	switch(direction) {
		case ACTION_WALK_NORTH:
			horizontal = 0; vertical = -1; facing = W_UP;
			sprite_position =
					(is_right_step)? SPRITE_FACING_NORTH_STEP_RIGHT : SPRITE_FACING_NORTH_STEP_LEFT;
			break;

		case ACTION_WALK_SOUTH:
			horizontal = 0; vertical = 1; facing = W_DOWN;
			sprite_position =
					(is_right_step)? SPRITE_FACING_SOUTH_STEP_RIGHT : SPRITE_FACING_SOUTH_STEP_LEFT;
			break;

		case ACTION_WALK_EAST:
			horizontal = 1; vertical = 0; facing = W_RIGHT;
			sprite_position =
					(is_right_step)? SPRITE_FACING_EAST_STEP_RIGHT : SPRITE_FACING_EAST_STEP_LEFT;
			break;

		case ACTION_WALK_WEST:
			horizontal = -1; vertical = 0; facing = W_LEFT;
			sprite_position =
					(is_right_step)? SPRITE_FACING_WEST_STEP_RIGHT : SPRITE_FACING_WEST_STEP_LEFT;
			break;
		case ACTION_NONE:
			switch(previous_action) {
				case ACTION_WALK_NORTH: sprite_position = SPRITE_FACING_NORTH_STOPPED; break;
				case ACTION_WALK_SOUTH: sprite_position = SPRITE_FACING_SOUTH_STOPPED; break;
				case ACTION_WALK_EAST: sprite_position = SPRITE_FACING_EAST_STOPPED; break;
				case ACTION_WALK_WEST: sprite_position = SPRITE_FACING_WEST_STOPPED; break;
				default: assert(0); break; /* Something is really wrong. */
			}
			break;
		default:
			debug("Invalid walk action received.");
			return;
	}

	if (direction != ACTION_NONE) {
		this->move_background_8px(horizontal, vertical);
		m_Character->set_facing_direction(facing);
	}

	previous_action = direction;
	is_right_step = !is_right_step;

	m_Character->set_sprite(sprite_position);
	m_Character->set_action_move_cooldown(ACTION_MOVE_COOLDOWN_CYCLES);
}

void GamePlay::move_background_8px(const int& x, const int& y)
{
	int relative_pos_x_px = TILE_8PX_TO_PX(m_Character->get_relative_pos_x_8px() + x);
	int relative_pos_y_px = TILE_8PX_TO_PX(m_Character->get_relative_pos_y_8px() + y);

	const st_rect char_coll_rect = m_Character->get_collision_rect();
	st_rect collision_element(char_coll_rect.pos.x + relative_pos_x_px,
								char_coll_rect.pos.y + relative_pos_y_px,
								char_coll_rect.w, char_coll_rect.h);

	if (m_MapProcessor.check_static_collision(collision_element) == 1) {
		return;
	}

	/* If can't scroll the background will not update the character relative position. */
	if (m_MapProcessor.move_map_8px(x, 0) == 0) {
		m_Character->add_relative_pos_x_8px(x);
	}

	if (m_MapProcessor.move_map_8px(0, y) == 0) {
		m_Character->add_relative_pos_y_8px(y);
	}

	//debug(" posRela: %d,%d (%d,%d)", TILE_8PX_TO_32PX(m_Pos_relative_8px.x),TILE_8PX_TO_32PX(m_Pos_relative_8px.y), m_Pos_relative_8px.x, m_Pos_relative_8px.y);
}

/*************************************************************************************************/
/* Declare touching action. */
static bool check_touch_points(st_offset touching[], vector<GameObject *> *objects_list, Trigger * &trigger_data);
static bool check_touched_object(st_offset touching, st_rect area);

void GamePlay::touch_action(void)
{
	/* Check cool down. */
	if (m_Character->get_action_touch_cooldown() > 0) {
		//debug("cool down: %d", m_Character->get_action_touch_cooldown());
		return;
	}

	Trigger *trigger_data;
	st_offset touching[2];

	memset(touching, 0 , sizeof(touching));

	m_Character->get_touch_position(touching);

	if (check_touch_points(touching, m_Scenery->get_ObjectsList(), trigger_data) == true) {
		m_ActionsQueue.push(trigger_data);
		debug("Push %d reaction.", trigger_data->get_Reaction());
	}

	/* Update cool down. */
	m_Character->set_action_touch_cooldown(ACTION_TOUCH_COOLDOWN_CYCLES);
}

/**
 * \brief Touch items on the scenery.
 * \parameter touching The touching points to be verified.
 * \parameter objects_list List of objects in the scenery to check.
 * \return true if touched and filled the trigger parameter; false otherwise.
 */
static bool check_touch_points(st_offset touching[], vector<GameObject *> *objects_list, Trigger * &trigger_data)
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
		if (object->get_reaction(ACTION_TOUCH, trigger_data) != true) {
			// Return if there is no reaction.
			return false;
		}

		debug("Reaction: %d; pt: %p", trigger_data->get_Reaction(), trigger_data);
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
/* Declare give object action. */
void GamePlay::give_object_action(const long& object_id)
{
	GameObject *object = m_Scenery->get_Object(object_id);

	/* If the object was not found, do nothing. If there is more lists that the object can be in,
	 * add here and keep searching before returning.
	 */
	if (object == NULL) {
		return;
	}

	// Add the item to the character.
	if (m_Character->add_object(object) != true) {
		debug("no more space.");
		// error message here!
		return;
	}

	// The object was taken. Now it is in the inventory. TODO: update the inventory window.
	// Set object visibility.
	object->set_Visibility(false);

	// Remove duplicated references.
	m_Scenery->remove_Object(object_id);

	debug("leaving");
}

/*************************************************************************************************/
/* Declare check for object action. */

void GamePlay::check_for_object_action(const long& object_id, Trigger *next)
{
	debug("Check of obj: %ld", object_id);
	if (m_Character->check_object(object_id) != true) {
		// The player had not found the object yet.
		return;
	}

	// The player found the object. Set the next trigger.
	if (next != NULL) {
		m_ActionsQueue.push(next);
	}
	// maybe we will need to delete the "next" guy in some situations.
}

/*************************************************************************************************/
/* Declare remove object action. */

void GamePlay::remove_object_action(const long& object_id, Trigger *next)
{
	debug("Delete obj: %ld", object_id);
	m_Character->delete_object(object_id);

	if (next != NULL) {
		m_ActionsQueue.push(next);
	}
}

/*************************************************************************************************/
/* Declare change sprite action. */
void GamePlay::change_sprite_action(const long& object_id, const int& new_sprite, Trigger *next)
{
	GameObject *object = m_Scenery->get_Object(object_id);
	if (object == NULL) {
		return;
	}
	/* If the object was not found, do nothing. If there is more lists that the object can be in,
	 * add here and keep searching before returning.
	 */
	object->set_sprite(new_sprite);

	if (next != NULL) {
		m_ActionsQueue.push(next);
	}
}

/*************************************************************************************************/

void GamePlay::change_reaction_action(const long& object_id, const en_action& reaction, Trigger *new_trigger)
{
	GameObject *object = m_Scenery->get_Object(object_id);
	if (object == NULL) {
		return;
	}

	object->disable_All_trigger(reaction);
	new_trigger->enable();
}
