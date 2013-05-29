#ifndef GAMEVIDEO_STRUCTS_HEADER
#define GAMEVIDEO_STRUCTS_HEADER

#include "gameVideo_defines.h"

/**
 * \b Structure that visually represents an element.
 */
typedef struct {
	int h;				//!< Horizontal position.
	int v;				//!< Vertical position.
	BITMAP *image;		//!< Bitmap that represents the element.
	unsigned int key;	//!< Key to access this element (maybe unused).
	en_visual_type type;	//!< Type of the visual element (used to unpack the figures).
} st_visual;

#endif /* GAMEVIDEO_STRUCTS_HEADER */
