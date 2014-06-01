/*
 * GameBoard.cpp
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#include <iostream>
#include <assert.h>


#include "GameBoard.h"
#include "Viewpoints.h"
#include "VisualElement.h"

#include "debug.h"
#include "scen0.h"

using namespace std;

/*************************************************************************************************/

GameBoard::GameBoard(Video *video):
m_Video(video),
m_Board(new VisualElement)
{
	/* Creates the board visual element, but don't add a surface to it. */
}

/*************************************************************************************************/

GameBoard::~GameBoard()
{
	delete m_Board;
}

/*************************************************************************************************/

void GameBoard::draw(void)
{
	st_element_pos tsize = {72,72};
	SDL_Surface *board = NULL;

	assert(Viewpoints::build_layer_hex(&board,
			layer0_bounds,
			layer0,
			"resources/tilesets/land.bmp",
			tsize) == 0);


	m_Board->set_viewpoint(board);

	m_Video->push_under_layer(m_Board);
	m_Video->start();
}

