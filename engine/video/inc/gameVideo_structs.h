#ifndef GAMEVIDEO_STRUCTS_HEADER
#define GAMEVIDEO_STRUCTS_HEADER

/**
 * \b Structure that visually represents an element.
 */
typedef struct {
	int h;				//!< Horizontal position.
	int v;				//!< Vertical position.
	BITMAP *image;		//!< Bitmap that represents the element.
	unsigned int key;	//!< Key to access this element (maybe unused).
} st_visual;

#endif /* GAMEVIDEO_STRUCTS_HEADER */
