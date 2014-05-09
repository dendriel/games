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

#include "VisualElement.h"

#define RED 255
#define GREEN 0
#define BLUE 255

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
	VisualElement foo, fa(50,50);

	SDL_Surface *img = SDL_LoadBMP("sprites/grass.bmp");
	SDL_SetColorKey(img , SDL_SRCCOLORKEY, SDL_MapRGB(img->format, RED, GREEN, BLUE));
	//assert(img);

	foo.set_viewpoint(img, 0);
	fa.set_viewpoint(img, 0);

	m_Video.add_visualElement(&foo);
	m_Video.add_visualElement(&fa);

	unsigned char width = 5;
	unsigned char height = 5;

	unsigned int hwidth = 32;
	unsigned int hheight = 16;


	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SDL_Surface *img = SDL_LoadBMP("sprites/warrior.bmp");
			cout << "x: " << int(hwidth*x) << " y: " << int(hheight*y) << endl;
			VisualElement fa (int(hwidth*x), int(hheight*y));
			fa.set_viewpoint(img, 0);
			m_Video.add_visualElement(&fa);
		}
	}
	m_Video.start();

	Sleep(3000);

	//SDL_FreeSurface(img);
}
