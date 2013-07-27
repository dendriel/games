/*
 * Critter.cpp
 *
 *  Created on: 23/07/2013
 *      Author: vitor
 */

#include "Critter.h"

#include <unistd.h>
#include <time.h>

#include "utils.h"

/*************************************************************************************************/
	Critter::Critter(const int x, const int y):
	VisualElement(x, y),
	m_Speed_ms(CRITTER_SPEED_MS),
	m_StandPosition(IMAGE_DOWN_STAND)
	{
		if (build_viewpoints(IMAGE_VIEWPOINTS_SOURCE_PATH, IMAGE_POSITIONS, IMAGE_VIEWS, &m_Viewpoints[0]) < 0) {
			cout << "Failed to build Critter viewpoints." << endl;
		}

		m_Critter_tid = SDL_CreateThread(&ai_thread_wrapper, this);
		cout << "Thread launched!! " << m_Critter_tid << endl;
	}

/*************************************************************************************************/
	void Critter::move_up(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_UP_LEFT);
		}
		else {
			set_viewposition(IMAGE_UP_RIGHT);
		}
		add_offset(0, CRITTER_WALK_LENGTH*-1);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_UP_STAND;
	}

/*************************************************************************************************/
	void Critter::move_right(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_RIGHT_LEFT);
		}
		else {
			set_viewposition(IMAGE_RIGHT_RIGHT);
		}
		add_offset(CRITTER_WALK_LENGTH, 0);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_RIGHT_STAND;
	}

/*************************************************************************************************/
	void Critter::move_left(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_LEFT_LEFT);
		}
		else {
			set_viewposition(IMAGE_LEFT_RIGHT);
		}
		add_offset(CRITTER_WALK_LENGTH*-1, 0);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_LEFT_STAND;
	}

/*************************************************************************************************/
	void Critter::move_down(void)
	{
		static bool left_foot_f = true;

		if (left_foot_f) {
			set_viewposition(IMAGE_DOWN_LEFT);
		}
		else {
			set_viewposition(IMAGE_DOWN_RIGHT);
		}
		add_offset(0, CRITTER_WALK_LENGTH);

		left_foot_f = !(left_foot_f);
		m_StandPosition = IMAGE_DOWN_STAND;
	}

/*************************************************************************************************/
	void Critter::stand(void)
	{
		set_viewposition(m_StandPosition);
	}

/*************************************************************************************************/
	int Critter::ai_thread(void)
	{
		const unsigned int max_actions = 5;
		int action;
		cout << "Critter thread is upline!!" << endl;
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
			cout << "Action: " << action << endl;
			usleep(m_Speed_ms*MILI);
		}

		return 0;
	}
