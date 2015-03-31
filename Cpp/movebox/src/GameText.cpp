/*
 * GameText.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: vitor
 */

#include "GameText.h"

#include "Utils.h"

GameText::GameText()
{
}

GameText::~GameText() {}


void GameText::setText(TTF_Font *text_font, std::string text, SDL_Color color, SDL_Renderer *renderer)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(text_font, text.c_str(), color);
	if( text_surface == NULL )
	{
		assert_exit("Unable to render text surface! SDL_ttf Error: " << TTF_GetError());
	}

	//Create texture from surface pixels
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if(texture == NULL)
	{
		assert_exit("Unable to create texture from rendered text! SDL Error: " << SDL_GetError());
	}

	setTexture(texture);
	setSize({0, 0, text_surface->w, text_surface->h});

	SDL_FreeSurface(text_surface);
}
