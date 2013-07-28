/*
 * Enemy.cpp
 *
 *  Created on: 23/07/2013
 *      Author: vitor
 */

#include "Enemy.h"

#include <unistd.h>
#include <time.h>

#include "utils.h"

/*************************************************************************************************/
	Enemy::Enemy(const int x, const int y,
			char *img_source, const unsigned int positions, const unsigned int views):
	VisualElement(x, y),
	m_Speed_ms(DEFAULT_SPEED_MS),
	m_StandPosition(IMAGE_DOWN_STAND),
	m_ImageSourcerPath(img_source),
	m_ImagePositions(positions),
	m_ImageViews(views)
	{
		if (build_viewpoints(m_ImageSourcerPath, m_ImagePositions, m_ImageViews, &m_Viewpoints[0]) < 0) {
			cout << "Failed to build Enemy viewpoints." << endl;
			/* Free any allocated position and Build here with default parameters. */
		}

		m_Enemy_tid = SDL_CreateThread(&ai_thread_wrapper, this);
		cout << "Thread launched!! " << m_Enemy_tid << endl;
	}

/*************************************************************************************************/
	void Enemy::move_up(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_UP_LEFT);
		}
		else {
			set_viewposition(IMAGE_UP_RIGHT);
		}
		add_offset(0, DEFAULT_WALK_LENGTH*-1);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_UP_STAND;
	}

/*************************************************************************************************/
	void Enemy::move_right(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_RIGHT_LEFT);
		}
		else {
			set_viewposition(IMAGE_RIGHT_RIGHT);
		}
		add_offset(DEFAULT_WALK_LENGTH, 0);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_RIGHT_STAND;
	}

/*************************************************************************************************/
	void Enemy::move_left(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_LEFT_LEFT);
		}
		else {
			set_viewposition(IMAGE_LEFT_RIGHT);
		}
		add_offset(DEFAULT_WALK_LENGTH*-1, 0);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_LEFT_STAND;
	}

/*************************************************************************************************/
	void Enemy::move_down(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_DOWN_LEFT);
		}
		else {
			set_viewposition(IMAGE_DOWN_RIGHT);
		}
		add_offset(0, DEFAULT_WALK_LENGTH);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_DOWN_STAND;
	}

/*************************************************************************************************/
	void Enemy::stand(void)
	{
		set_viewposition(m_StandPosition);
	}

/*************************************************************************************************/
	int Enemy::ai_thread(void)
	{
		const unsigned int max_actions = 5;
		int action;
		cout << "Enemy thread is upline!!" << endl;
		while(true) {

			/*for (int i=0; i < IMAGE_POSITIONS*IMAGE_VIEWS; ++i) {
				set_viewposition(i);
				usleep(900*1000);
			}*/

			srand(time(NULL)*(int)(this));
			action = (rand() % max_actions);

			switch (action) {
			// UP;
			case 0:
				move_up();
				break;
			// RIGHT
			case 1:
				move_right();
				break;
			// DOWN:
			case 2:
				move_down();
				break;
			// LEFT
			case 3:
				move_left();
				break;
			// STAND
			case 4:
				stand();
				usleep(m_Speed_ms*MILI);
				break;
			default:
				cout << "invalid action: " << action << endl;
				break;
			}
			usleep(m_Speed_ms*MILI);
		}

		return 0;
	}
