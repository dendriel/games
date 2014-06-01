/*
 * GameBoard.h
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <tr1/cstdint>

#include "Video.h"

class GameBoard {
	Video *m_Video;
	VisualElement *m_Board;	//!< Visual element that represents the game board.

public:
	/*
	 * Constructor.
	 * \note In the first mode, the game board object will only be declared.
	 * In the second mode, the game board object will create a surface with w and h to draw the
	 * gaming board.
	 */
	GameBoard(Video *video);

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
