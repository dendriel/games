/*
 * VisualElement.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "VisualElement.h"

using namespace std;

VisualElement::VisualElement():
_pos({0,0}),
_size({0,0}),
_curr_sprite("")
{
	// TODO Auto-generated constructor stub

}

VisualElement::~VisualElement()
{
	// TODO Auto-generated destructor stub
}


void VisualElement::setPos(SDL_Point pos)
{
	_pos = pos;
}

void VisualElement::setSize(SDL_Point size)
{
	_size = size;
}

void VisualElement::addSprite(std::string sprite)
{
	sprite_list.push_back(sprite);
	_curr_sprite = sprite;
}

string VisualElement::curr_sprite(void)
{
	return _curr_sprite;
}

SDL_Point VisualElement::pos(void)
{
	return _pos;
}
