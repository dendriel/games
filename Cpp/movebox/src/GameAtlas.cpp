/*
 * GameAtlas.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "GameAtlas.h"

#include <iostream>

#include <assert.h>

#include "Utils.h"


using namespace std;

GameAtlas::GameAtlas()
{
	// TODO Auto-generated constructor stub

}

GameAtlas::~GameAtlas()
{
	clearAllSheets();

	for (auto const& p : texture_list)
	{
		SDL_DestroyTexture(p.second);
	}
	texture_list.clear();
}

void GameAtlas::addSheet(Spritesheet *sheet)
{
	sheet_list.push_back(sheet);
}

void GameAtlas::clearAllSheets(void)
{
	sheet_list.clear();
}

Spritesheet *GameAtlas::getSheet(const string name)
{
	GameSprite *sprite = NULL;

	for (vector<Spritesheet *>::iterator iter = sheet_list.begin(); iter != sheet_list.end(); iter++)
	{
		Spritesheet *sheet = *iter;

		sprite = sheet->getSprite(name);
		if (sprite != NULL)
		{
			return sheet;
		}
	}

	return NULL;
}

Spritesheet *GameAtlas::getSheet(const int id)
{
	GameSprite *sprite = NULL;

	for (vector<Spritesheet *>::iterator iter = sheet_list.begin(); iter != sheet_list.end(); iter++)
	{
		Spritesheet *sheet = *iter;

		sprite = sheet->getSprite(id);
		if (sprite != NULL)
		{
			return sheet;
		}
	}

	return NULL;
}

void GameAtlas::addTexture(const std::string name, SDL_Renderer *renderer)
{
	SDL_Texture *texture = Utils::loadTexture(name, renderer);
	texture_list[name] = texture;
}

/**
 * @brief Use a texture from the atlas.
 */
SDL_Texture *GameAtlas::getTexture(const std::string name)
{
	if (texture_list.find(name) == texture_list.end())
	{
		return NULL;
	}

	return texture_list[name];
}
