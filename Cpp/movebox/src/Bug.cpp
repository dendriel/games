/*
 * Bug.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#include "Bug.h"

#include <iostream>

using namespace std;

Bug::Bug(const string sprite_name, const int x, const int y)
{
	addSprite(sprite_name);
	setPos({x, y});
}

Bug::~Bug() {}

void Bug::addPos(SDL_Point pos)
{
	// East.
	if (pos.x > 0)
	{
		setRotated(true);
		setRotationAngleDegrees(90);
	}
	// West.
	else if (pos.x < 0)
	{
		setRotated(true);
		setRotationAngleDegrees(-90);
	}
	// South.
	else if (pos.y > 0)
	{
		setRotated(true);
		setRotationAngleDegrees(180);
	}
	// North.
	else
	{
		setRotated(false);
	}

	VisualElement::addPos(pos);
}

