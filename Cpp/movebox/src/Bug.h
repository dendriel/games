/*
 * Bug.h
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#ifndef BUG_H_
#define BUG_H_

#include <string>

#include "VisualElement.h"

#include "Utils.h"


class Bug: public VisualElement
{
public:
	Bug(const std::string sprite_name, const int x, const int y);
	virtual ~Bug();

	void addPos(SDL_Point pos);
};

#endif /* BUG_H_ */
