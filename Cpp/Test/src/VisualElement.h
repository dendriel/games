/*
 * VisualElement.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef VISUALELEMENT_H_
#define VISUALELEMENT_H_

#include <string>
#include <vector>

#include <SDL.h>

class VisualElement {
private:

	SDL_Point _pos;
	SDL_Point _size;
	std::string _curr_sprite;
	std::vector<std::string> sprite_list;

public:
	VisualElement();
	virtual ~VisualElement();

	void setPos(SDL_Point pos);
	void setSize(SDL_Point size);
	void addSprite(std::string sprite);

	std::string curr_sprite(void);
	SDL_Point pos(void);
};

#endif /* VISUALELEMENT_H_ */
