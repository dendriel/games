#ifndef GVIDEO_DEFINES_HEADER
#define GVIDEO_DEFINES_HEADER

#define GVIDEO_MQUEUE_NAME			"/gameVideo_queue"	//!< Queue name for game video module.
#define GVIDEO_SCREEN_UPDATE_US		50*1000				//!< Update the screen every 50 miliseconds.
#define GVIDEO_MAX_QUEUE_MSG		1024				//!< Maximum number of queued messages.
#define GVIDEO_INVALID_KEY			-1					//!< Used to indicate that the request was not sucessfully processed.

#define GVIDEO_MAX_ELEM_BMP			20					//!< 4*4 are default element view; 4 are reserved.
#define GVIDEO_ELEM_SIZE_H			32					//!< Element default horizontal size.
#define GVIDEO_ELEM_SIZE_V			48					//!< Element default vertical size.

/**
 *	\b Visual elements types.
 */
typedef enum {
	GVIDEO_VTYPE_SCEN_STATIC = 1,		//!< Static scenery.
	GVIDEO_VTYPE_SCEN_DYNAMIC,			//!< Dynamic scenery.
	GVIDEO_VTYPE_ELEM_STATIC,			//!< Static element.
	GVIDEO_VTYPE_ELEM_DYNAMIC,			//!< Dynamic element.
	GVIDEO_VTYPE_MAX_ELEM				//!< Used to validate valid range. MUST be the last item.
} en_visual_type;

/**
 *	\b Visual element images positions in the image array.
 */
typedef enum {
	GVIDEO_IMG_SRC = 0,			//!< The entire image from where the anothers were splitted.
	GVIDEO_IMG_FRONT_0,
	GVIDEO_IMG_FRONT_1,
	GVIDEO_IMG_FRONT_2,
	GVIDEO_IMG_FRONT_3,
} en_visual_image_pos;

#endif /* GVIDEO_DEFINES_HEADER */
