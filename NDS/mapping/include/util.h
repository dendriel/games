/*
 * util.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <nds.h>
#include "timming.h"

/* Macros */
#define debug(fmt,args...) (void)(iprintf(fmt"\n",##args))

#define loop() while(1) GSLEEP(1);

/* Helpful structures. */

//!< Hold screen matrix coordinates.
typedef struct st_offset {
	int x;
	int y;
	st_offset(int _x=0, int _y=0):
		x(_x),
		y(_y){};
} st_offset;

//!< Hold a rectangle size and screen positioning.
typedef struct {
	st_offset pos;
	size_t w;
	size_t h;
} st_rect_size;

//!< Hold data about a background (used to load it).
typedef struct {
	int id;					//!< Background ID. Returned by bgInit() function.
	int layer;				//!< Background hardware layer to init.  Must be 0 - 3. (retrieved from bgInit documentation).
	BgType type;			//!< The type of background to init. (retrieved from bgInit documentation).
	BgSize size;			//!< The size of the background. (retrieved from bgInit documentation).
	int dataBase;			//!< VRAM offset.
	int tileBase;			//!< The 16k offset into VRAM the tile graphics data will be placed. (retrieved from bgInit documentation).
	unsigned int prio;		//!< The layer priority to be draw in the screen.
	const unsigned short *data;	//!< Pointer to the layer data.
} st_map_bg;

//!< Hold character facing direction.
typedef enum {
	W_UP	= 0,
	W_RIGHT	= 1,
	W_DOWN	= 2,
	W_LEFT	= 3,
	W_DEFAULT		//!< None direction or keep the previous direction.
} en_facing;

typedef enum {
	STEP_RIGHT = 0,
	STEP_LEFT = 1
} en_cur_step;

/*
 * \brief Define the screen quarter that will be worked. For example:
 * first|second
 *  1111|2222
 *  1111|2222
 *  ---------
 *  3333|4444
 *  3333|4444
 * third|fourth
 */
typedef enum {
	FIRST_QUARTER = 0,
	SECOND_QUARTER,
	THIRD_QUARTER,
	FOURTH_QUARTER
} en_screen_quarter;

/* Helpful definitions. */
#define SCREEN_CENTER_X SCREEN_WIDTH/2		/* 256/2 = 128 = tile 4 */
#define SCREEN_CENTER_Y SCREEN_HEIGHT/2		/* 192/2 = 96 = tile 3*/

#define SPRITE_SCREEN_CENTER_X SCREEN_CENTER_X//-16
#define SPRITE_SCREEN_CENTER_Y SCREEN_CENTER_Y-4

#define SPRITE_SCREEN_CENTER_X_TILES 4
#define SPRITE_SCREEN_CENTER_Y_TILES 3

#define SCREEN_WIDTH_IN_TILES 8
#define SCREEN_HEIGHT_IN_TILES 6

#define TILE_W_SIZE 32
#define TILE_H_SIZE TILE_W_SIZE

#define SCREEN_DRAW_BOUND_X(_size_x) _size_x - SCREEN_WIDTH
#define SCREEN_DRAW_BOUND_Y(_size_y) _size_y - SCREEN_HEIGHT

#endif /* UTIL_H_ */
