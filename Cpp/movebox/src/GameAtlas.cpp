/*
 * GameAtlas.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "GameAtlas.h"

#include <iostream>

#include <assert.h>

using namespace std;

GameAtlas::GameAtlas()
{
	// TODO Auto-generated constructor stub

}

GameAtlas::~GameAtlas()
{
	sheet_list.clear();
}

void GameAtlas::addSheet(Spritesheet *sheet)
{
	sheet_list.push_back(sheet);
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

	cout << "The requested sprite's sheet \"" << name << "\" doesn't exist!" << endl;
	assert(0);

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

	cout << "The requested sprite's sheet \"" << id << "\" doesn't exist!" << id;
	assert(0);

	return NULL;

}
