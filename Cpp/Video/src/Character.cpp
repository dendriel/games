/*
 * Character.cpp
 *
 *  Created on: 31/07/2013
 *      Author: vitor
 */

#include "Character.h"

/*************************************************************************************************/
Character::Character(const int x, const int y,
		string img_source, const unsigned int positions, const unsigned int views):
	VisualElement(x, y),
	CollisionElement(ANIMATED),
	m_StandPosition(IMAGE_DOWN_STAND),
	m_ImageSourcerPath(img_source),
	m_ImagePositions(positions),
	m_ImageViews(views),
	m_Speed_ms(CHAR_DEFAULT_SPEED_MS)
{
	if (build_viewpoints(m_ImageSourcerPath.c_str(), m_ImagePositions, m_ImageViews, &m_Viewpoints[0]) < 0) {
		cout << "Failed to build Character viewpoints." << endl;
		/* Free any allocated position and Build here with default parameters. */
	}
	cout << "Character object created!" << endl;
}

/*************************************************************************************************/


/*************************************************************************************************/
void Character::move_up(void)
{
	static bool left_foot_f = true;

	if (left_foot_f) {
		set_viewposition(IMAGE_UP_LEFT);
	}
	else {
		set_viewposition(IMAGE_UP_RIGHT);
	}
	add_offset(0, CHAR_DEFAULT_WALK_LENGTH*-1);

	left_foot_f = !(left_foot_f);
	m_StandPosition = IMAGE_UP_STAND;
}

/*************************************************************************************************/
void Character::move_right(void)
{
	static bool left_foot_f = true;

	if (left_foot_f) {
		set_viewposition(IMAGE_RIGHT_LEFT);
	}
	else {
		set_viewposition(IMAGE_RIGHT_RIGHT);
	}
	add_offset(CHAR_DEFAULT_WALK_LENGTH, 0);

	left_foot_f = !(left_foot_f);
	m_StandPosition = IMAGE_RIGHT_STAND;
}

/*************************************************************************************************/
void Character::move_left(void)
{
	static bool left_foot_f = true;

	if (left_foot_f) {
		set_viewposition(IMAGE_LEFT_LEFT);
	}
	else {
		set_viewposition(IMAGE_LEFT_RIGHT);
	}
	add_offset(CHAR_DEFAULT_WALK_LENGTH*-1, 0);

	left_foot_f = !(left_foot_f);
	m_StandPosition = IMAGE_LEFT_STAND;
}

/*************************************************************************************************/
void Character::move_down(void)
{
	static bool left_foot_f = true;

	if (left_foot_f) {
		set_viewposition(IMAGE_DOWN_LEFT);
	}
	else {
		set_viewposition(IMAGE_DOWN_RIGHT);
	}
	add_offset(0, CHAR_DEFAULT_WALK_LENGTH);

	left_foot_f = !(left_foot_f);
	m_StandPosition = IMAGE_DOWN_STAND;
}

/*************************************************************************************************/
void Character::stand(void)
{
	set_viewposition(m_StandPosition);
}
