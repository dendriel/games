/*
 * GameScenery.cpp
 *
 *  Created on: 20/10/2013
 *      Author: marta
 */

#include "GameScenery.h"
#include "util.h"

/*************************************************************************************************/

void GameScenery::check_touch_points(st_offset touching[])
{
	//debug("pa: %d,%d; pb: %d,%d", touching[0].x, touching[0].y, touching[1].x, touching[1].y);

	for (std::vector<GameObject *>::iterator iter = m_ObjectsList.begin();
			iter != m_ObjectsList.end(); ++ iter) {
		GameObject *object = *iter;
		st_rect relative_coor;

		relative_coor.pos.x = object->get_CollRect().pos.x + object->get_Pos_relative_px().x;
		relative_coor.pos.y = object->get_CollRect().pos.y + object->get_Pos_relative_px().y;
		relative_coor.w = relative_coor.pos.x + object->get_CollRect().w;
		relative_coor.h = relative_coor.pos.y + object->get_CollRect().h;

		// Check p1.
		if (this->check_touched_object(touching[0], relative_coor) == true) {
			debug("Touched object %s!", object->get_Name().c_str());
		}
		// Check p2.
		else if (this->check_touched_object(touching[1], relative_coor) == true) {
			debug("Touched object %s!", object->get_Name().c_str());
		}
		else {
//			debug("Touched nothing!");
		}
	}
}

/*************************************************************************************************/

bool GameScenery::check_touched_object(st_offset touching, st_rect area)
{
	//debug("area: %d,%d; %d,%d", area.pos.x, area.pos.y, area.w, area.h);

	if (touching.x >= area.pos.x && touching.y >= area.pos.y &&
			touching.x <= static_cast<int>(area.w) && touching.y <= static_cast<int>(area.h)) {
		return true;
	}

	return false;
}
