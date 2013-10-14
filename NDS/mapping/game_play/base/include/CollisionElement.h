/*
 * CollisionElement.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONELEMENT_H_
#define COLLISIONELEMENT_H_

#include "util.h"

/**
 *  In order to collision checking an game element, it needs to be a collision element. Being
 * a collision element means that the element have it own collision area, that will be checked
 * with another collision areas/element from the game.
 *  To start the game is checking by static collision, that does not demand a lot of work, but
 * just demands that before moving the element ask if can go to the wanted position.
 * The st_rect will define a rectangle that represents the area of collision of the element. The
 * element, by his time, have his relative and absolute position in the game map. To collision
 * checking, will be necessary only the relative position. Checking against static collision is
 * to verify if the next tile 32x32 is blocked by something, however, the collision element don't
 * need to have a 32x32 rectangle area. It will have his rectangle of any size between 0,0-31,21
 * that will be checked in the GameMapProcessor. Take a look how it works:
 *
 *
 *
 * Game Tile 32x32 px.
 *
 * 0   4   8  12  16  20  24  28  31
 * +---+---+---+---+---+---+---+---
 * |
 * |
 * |
 * |	 x,y    x1,y
 * |      +-----+
 * |      |     |
 * |      |     |
 * |      +-----+
 * |    x,y1   x1,y1
 * |
 * |
 * |
 * +---+---+---+---+---+---+---+---
 *
 * The square in the center is the st_rect that represents the collision area of an element. The collision
 * checking will be made........ TODO
 *
 *  Try to explain that each element is seen as being inside a tile (every time). But its sprite can not fulfill
 *  a tile, and the x,y; x1,y; x,y1; x1,y1 is the relative position of the element plus its rectangle size. The
 *  x, y of the rectangle tells the offset of the inside the tile.
 *
 *
 * Next, the x's represents the touching points of a collision element. The represented area will be the
 * "action collision area".
 *
 * 0   4   8  12  16  20  24  28  31
 * +---+---+---+---+---+---+---+---
 * |                  Y:
 * | X: p1  p2p3  p4
 * |
 * |	    x x       p1
 * |      +-----+
 * |    x |     | x   p2
 * |    x |     | x   p3
 * |      +-----+
 * |        x x       p4
 * |
 * |
 * |
 * +---+---+---+---+---+---+---+---
 */

class CollisionElement {
protected:
	st_rect m_CollRect;
	st_rect m_ActionCollRect;

public:
	CollisionElement(const st_rect rect, const st_rect action_rect);
};


#endif /* COLLISIONELEMENT_H_ */
