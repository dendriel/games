/*
 * game_defines.h
 *
 *  Created on: 28/05/2014
 *      Author: vitor
 */

#ifndef GAME_DEFINES_H_
#define GAME_DEFINES_H_

#include <tr1/cstdint>

//!< Screen dimensions. 16:9 == 960x540; 4:3 == 800x600; 16:9 == 1280×720
#define GAME_SCREEN_W (uint16_t) 1280	//!< Hard screen width.
#define GAME_SCREEN_H (uint16_t) 720	//!< Hard screen height.

//!< Board screen dimensions.
#define GAME_BOARD_SCREEN_W GAME_SCREEN_W*0.8	//!< Board width - 80% of the hard screen width.
#define GAME_BOARD_SCREEN_H GAME_SCREEN_H		//!< Board height - 100% of the hard screen height.
#define GAME_BOARD_SCREEN_X 0					//!< Board horizontal offset.
#define GAME_BOARD_SCREEN_Y 0					//!< Board vertical offset.

//!< Menu screen dimensions (inside the game-play).
#define GAME_MENU_SCREEN_W GAME_SCREEN_W*0.2		//!< Game-play menu width - 20% of the hard screen width.
#define GAME_MENU_SCREEN_H GAME_SCREEN_H			//!< Game-play menu height - 100% of the hard screen height.
#define GAME_MENU_SCREEN_X GAME_BOARD_SCREEN_W		//!< Game-play menu horizontal offset. Starts where the board finishes.
#define GAME_MENU_SCREEN_Y 0						//!< Game-play menu horizontal offset.

/**
 * The game-play screen will be something like the following:
 *
 *             board (80%)         menu (20%)
 * +------------------------------+--------+
 * |                              |        |
 * |                              |        |
 * |                              |        |
 * |                              |        |
 * |                              |        |
 * |                              |        |
 * |                              |        |
 * +---------------------------------------+
 *
 */


//!< Game title.
#define GAME_TITLE "Warfare"


#endif /* GAME_DEFINES_H_ */
