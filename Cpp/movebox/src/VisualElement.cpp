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
_curr_sprite(""),
_texture(NULL)
{
	// TODO Auto-generated constructor stub

}

VisualElement::~VisualElement()
{
	if (_texture != NULL)
	{
		SDL_DestroyTexture(_texture);
		_texture = NULL;
	}
}
