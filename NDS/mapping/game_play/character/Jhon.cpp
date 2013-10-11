/*
 * Jhon.cpp
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#include "Jhon.h"

//! Can't go through the walls.
//static st_rect Jhon_rect_size(8,8,15,23);
//! Overlay the walls.
static st_rect Jhon_rect_size(8,24,15,7);

Jhon::Jhon(const unsigned int x, const unsigned int y):
GameCharacter(Jhon_rect_size, (u8*)manTiles, x, y)
{
	;;
}
