/*
 * Critter.h
 *
 *  Created on: 23/07/2013
 *      Author: vitor
 */
#include <iostream>
#include <assert.h>

#include "SDL/SDL.h"

#include "VisualElement.h"
#include "viewpoints.h"

using namespace std;

#define IMAGE_VIEWPOINTS_SOURCE_PATH "image/aranha_288x320.bmp"
#define IMAGE_VIEWS 3			//!< How much views are in the image.
#define IMAGE_POSITIONS 4		//!< How much positions are in the image.


#define CRITTER_SPEED_MS 200
#define CRITTER_WALK_LENGTH 20


class Critter: public VisualElement {
private:
	SDL_Thread *m_Critter_tid;
	unsigned int m_Speed_ms;
	en_image_viewpoints m_StandPosition;

public:
	Critter(const int x = 0, const int y = 0);

	void move_up();
	void move_right();
	void move_left();
	void move_down();
	void stand();


	static int ai_thread_wrapper(void* pParam)
	{
		return ((Critter*)pParam)->ai_thread();
	}

private:
	int ai_thread(void);
};
