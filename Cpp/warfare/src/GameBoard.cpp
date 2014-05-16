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
#include "Controller.h"
#include "Viewpoints.h"
#include "VisualElement.h"
#include "debug.h"
#include "scen0.h"



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


int load_surface(const char *source, SDL_Surface **surface);

void GameBoard::draw()
{
	Controller control;
	//VisualElement foo(100, 100);

	//SDL_Surface *img = NULL;
	//assert(load_surface("resources/sprites/warrior.bmp", &img) == 0);
	//foo.set_viewpoint(img, 0);

	SDL_Surface *board = NULL;
	st_element_pos tsize = {72,72};
	Viewpoints::build_layer_hex(&board, layer0_bounds, layer0, "resources/tilesets/land.bmp", tsize);

	//m_Video.add_visualElement(&foo);

	m_Video.push_under_layer(board);

	m_Video.start();

	control.get_keyDown();

	control.get_keyDown();
}


// Put this function in the Viewpoints class.
int load_surface(const char *source, SDL_Surface **surface)
{
	SDL_Surface *image_source;

	CHK_NULL(image_source = SDL_LoadBMP(source));
	CHK_NULL((*surface = SDL_DisplayFormat(image_source)));

	SDL_SetColorKey(*surface , SDL_SRCCOLORKEY, SDL_MapRGB((*surface)->format, RED, GREEN, BLUE));

	return 0;
}

