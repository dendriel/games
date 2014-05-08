/*
 * GameBoard.cpp
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#include <iostream>
#include "assert.h"
#include "GameBoard.h"

#include "VisualElement.h"

GameBoard::GameBoard(Video& video, unsigned int width, unsigned int height):
m_Video(video),
m_Width(width),
m_Height(height)
{
	// TODO Auto-generated constructor stub

}

GameBoard::~GameBoard() {
	// TODO Auto-generated destructor stub
}

void GameBoard::draw()
{
	VisualElement foo;

	SDL_Surface *img = SDL_LoadBMP("sprites/warrior.bmp");
	//assert(img);

	foo.set_viewpoint(img, 0);

	m_Video.add_visualElement(&foo);
	m_Video.start();

	int a;
	std::cin >> a;

	SDL_FreeSurface(img);
}
