/*
 * Jack.cpp
 *
 *  Created on: 12/10/2013
 *      Author: vitor
 */

#include "Jack.h"

//! Overlay the walls.
static st_rect Jack_rect_size(8,16,8,15);

Jack::Jack(const unsigned int x, const unsigned int y):
GameCharacter(Jack_rect_size, (u8*)jack_charsetTiles, x, y)
{
	;;
}
