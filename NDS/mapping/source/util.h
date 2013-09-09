/*
 * util.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>

/* Macros */
#define debug(fmt,args...) (void)(iprintf(fmt"\n",##args))

/* Helpful structures. */

//!< Hold screen matrix coordinates.
typedef struct {
	int x;
	int y;
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
	W_LEFT	= 3,
	W_DOWN	= 2,
	W_RIGHT	= 1
} en_facing;

/* Helpful definitions. */
#define SCREEN_CENTER_X SCREEN_WIDTH/2
#define SCREEN_CENTER_Y SCREEN_HEIGHT/2

#endif /* UTIL_H_ */
