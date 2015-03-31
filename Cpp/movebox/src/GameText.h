/*
 * GameText.h
 *
 *  Created on: Mar 30, 2015
 *      Author: vitor
 */

#ifndef GAMETEXT_H_
#define GAMETEXT_H_

#include "SDL.h"
#include "SDL_ttf.h"

#include "VisualElement.h"

class GameText: public VisualElement
{

public:
	GameText();
	virtual ~GameText();
	void setText(TTF_Font *text_font, std::string text, SDL_Color color, SDL_Renderer *renderer);
};

#endif /* GAMETEXT_H_ */
