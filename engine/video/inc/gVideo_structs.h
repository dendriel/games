#ifndef GVIDEO_STRUCTS_HEADER
#define GVIDEO_STRUCTS_HEADER

#include <allegro.h>
#include "gVideo_defines.h"

/**
 * \b Structure that visually represents an element.
 */
typedef struct {
	int h;					//!< Horizontal position.
	int v;					//!< Vertical position.
	BITMAP *image[GVIDEO_MAX_ELEM_BMP];		//!< Bitmap that represents the element.
	unsigned int img_index;	//!< Identify what image must be in the screen at the updated.
	en_visual_type type;	//!< Type of the visual element (used to unpack the figures).
	int key;				//!< Key to access this element (maybe unused).
} st_visual;

#endif /* GVIDEO_STRUCTS_HEADER */
