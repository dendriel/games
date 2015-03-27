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
	SDL_Rect _size;
	std::string _curr_sprite;
	std::vector<std::string> sprite_list;
	SDL_Texture *_texture;	// If not NULL, the GameVideo will draw only this texture from the elem.

public:
	VisualElement();
	virtual ~VisualElement();

	inline void setPos(SDL_Point pos)
	{
		_pos = pos;
	}

	inline void setSize(SDL_Rect size)
	{
		_size = size;
	}

	inline SDL_Rect size(void)
	{
		return _size;
	}

	inline void addSprite(std::string sprite)
	{
		sprite_list.push_back(sprite);
		_curr_sprite = sprite;
	}

	inline void setTexture(SDL_Texture *texture)
	{
		_texture = texture;
	}

	inline SDL_Texture *texture(void)
	{
		return _texture;
	}

	std::string curr_sprite(void)
	{
		return _curr_sprite;
	}

	SDL_Point pos(void)
	{
		return _pos;
	}
};

#endif /* VISUALELEMENT_H_ */