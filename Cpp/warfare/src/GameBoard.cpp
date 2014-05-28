/*
 * GameBoard.cpp
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#include <iostream>
#include <Windows.h>
#include "assert.h"
#include "GameBoard.h"
#include "Viewpoints.h"
#include "VisualElement.h"
#include "debug.h"
#include "scen0.h"



GameBoard::GameBoard(Video *video, unsigned int width, unsigned int height):
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
	st_element_pos tsize = {72,72};
	SDL_Surface *board = NULL;
	Viewpoints::build_layer_hex(&board, layer0_bounds, layer0, "resources/tilesets/land.bmp", tsize);

	VisualElement *b = new VisualElement;
	b->set_viewpoint(board, 0);

	m_Video->push_under_layer(b);

	m_Video->start();
}

