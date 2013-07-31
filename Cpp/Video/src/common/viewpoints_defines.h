/*
 * viewpoints_defines.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef VIEWPOINTS_DEFINES_H_
#define VIEWPOINTS_DEFINES_H_

/**
 * Constants.
 */
//!< Default tile set data source.
#define TILESET_SOURCE "image/basic_tileset_128x128.bmp"
//!< Default tile size.
#define TILE_SIZE 32

/**
 * Enumerations.
 */
typedef enum {
	IMAGE_DOWN_STAND = 0,
	IMAGE_DOWN_RIGHT,
	IMAGE_DOWN_LEFT,
	IMAGE_RIGHT_STAND,
	IMAGE_RIGHT_RIGHT,
	IMAGE_RIGHT_LEFT,
	IMAGE_LEFT_STAND,
	IMAGE_LEFT_RIGHT,
	IMAGE_LEFT_LEFT,
	IMAGE_UP_STAND,
	IMAGE_UP_RIGHT,
	IMAGE_UP_LEFT
} en_image_viewpoints;


/**
 * Structures.
 */
//!< Represents a cartographic position.
typedef struct {
	int x;
	int y;
} st_element_pos;

#endif /* VIEWPOINTS_DEFINES_H_ */
