/*
 * Enemy.h
 *
 *  Created on: 23/07/2013
 *      Author: vitor
 */
#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <assert.h>

#include "SDL/SDL.h"

#include "VisualElement.h"
#include "CollisionElement.h"
#include "viewpoints.h"

using namespace std;


#define DEFAULT_SPEED_MS 200
#define DEFAULT_WALK_LENGTH 20
#define DEFAULT_IMAGE_SOURCE_PATH "aranha_288x320.bmp"
#define DEFAULT_IMAGE_POSITIONS 4
#define DEFAULT_IMAGE_VIEWS 3


class Enemy: public VisualElement, public CollisionElement {
private:
	SDL_Thread *m_Enemy_tid;
	unsigned int m_Speed_ms;
	en_image_viewpoints m_StandPosition;
	string m_ImageSourcerPath;
	unsigned int m_ImagePositions;
	unsigned int m_ImageViews;

public:
	Enemy(const int x = 0, const int y = 0,
			string img_source = DEFAULT_IMAGE_SOURCE_PATH,
			const unsigned int postions = DEFAULT_IMAGE_POSITIONS,
			const unsigned int views = DEFAULT_IMAGE_VIEWS);

	void move_up();
	void move_right();
	void move_left();
	void move_down();
	void stand();


	static int ai_thread_wrapper(void* pParam)
	{
		return ((Enemy*)pParam)->ai_thread();
	}

private:
	int ai_thread(void);
};

#endif /* ENEMY_H_ */