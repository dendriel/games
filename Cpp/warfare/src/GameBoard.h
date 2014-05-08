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
	unsigned int m_Width;
	unsigned int m_Height;

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
