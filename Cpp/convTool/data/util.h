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
#define debug(fmt,args...) (void)(printf(fmt"\n",##args))

/* Helpful structures. */

//!< Hold screen matrix coordinates or data dimensions.
typedef struct {
	union {
		int x, w;
	};
	union {
		int y, h;
	};
} st_offset;

//!< Hold a rectangle size and screen positioning.
typedef struct {
	st_offset pos;
	size_t w;
	size_t h;
} st_rect_size;

typedef struct {
	const unsigned short *map;		//!< Hold the tileset map.
	const unsigned int *data;		//!< Hold the tileset data.
	st_offset dim_tiles;	//!< Tileset dimensions.
	size_t len_bytes;		//!< Hold the tileset length.
	size_t len_memb;		//!< Hold the tileset size in members.
} st_tileset;

//!< Hold data about a background (used to load it).
typedef struct {
	int id;						//!< Background ID. Returned by bgInit() function.
	int layer;					//!< Background hardware layer to init.  Must be 0 - 3. (retrieved from bgInit documentation).
	//BgType type;				//!< The type of background to init. (retrieved from bgInit documentation).
	//BgSize size;				//!< The size of the background. (retrieved from bgInit documentation).
	int dataBase;				//!< VRAM offset.
	int tileBase;				//!< The 16k offset into VRAM the tile graphics data will be placed. (retrieved from bgInit documentation).
	unsigned int prio;			//!< The layer priority to be draw in the screen.
	const unsigned int *data;	//!< Pointer to the layer data.
	unsigned int width_tiles;	//!< Width in tiles.
	unsigned int height_tiles;	//!< Height in tiles.
	st_tileset tileset;			//!< Hold tileset data.
	const unsigned short *palette;	//!< Background palette.
	size_t palette_len_bytes;	//!< Background palette length.

} st_map_bg;


/* Structures */

//!< Hold data from an integer map and the current tile position.
typedef struct {
	//!< Position of an element in the array.
	struct size {
		int w;
		int h;
	} size_tiles;
	union {
		//!< Origin map data.
		unsigned int *uint_data;
		//!< Destination map data.
		unsigned short *ushort_data;
		//!< Tileset data.
		const unsigned short *cushort_data;
	};
	//!< Map data length in members (unsigned short, 2 bytes each).
	size_t length_memb;
} st_map_data;

//!< Hold character facing direction.
typedef enum {
	W_UP	= 0,
	W_LEFT	= 3,
	W_DOWN	= 2,
	W_RIGHT	= 1
} en_facing;

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
#define SCREEN_CENTER_X SCREEN_WIDTH/2
#define SCREEN_CENTER_Y SCREEN_HEIGHT/2
#define SCREEN_DRAW_BOUND_X(_size_x) _size_x - SCREEN_WIDTH
#define SCREEN_DRAW_BOUND_Y(_size_y) _size_y - SCREEN_HEIGHT
#define SCREEN_WIDTH_IN_TILES 8
#define SCREEN_HEIGHT_IN_TILES 6

#endif /* UTIL_H_ */
