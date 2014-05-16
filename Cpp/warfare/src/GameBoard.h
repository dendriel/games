/*
 * GameBoard.h
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "Video.h"

class GameBoard {
	Video& m_Video;
	unsigned int m_Width;	// Board width in hexagonal tiles.
	unsigned int m_Height;	// Board height in hexagonal tiles.

public:
	/*
	 * Constructor.
	 */
	GameBoard(Video& video, unsigned int width, unsigned int height);

	/*
	 * Destructor.
	 */
	virtual ~GameBoard();

	/*
	 * Main line.
	 */
	void draw(void);
};

#endif /* GAMEBOARD_H_ */
