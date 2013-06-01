#ifndef GVIDEO_DEFINES_HEADER
#define GVIDEO_DEFINES_HEADER

#define GAMEVIDEO_MQUEUE_NAME			"/gameVideo_queue"	//!< Queue name for gameVideo module.
#define GAMEVIDEO_SCREEN_UPDATE_US		50*1000				//!< Update the screen every 50 miliseconds.
#define GAMEVIDEO_MAX_QUEUE_MSG			1024				//!< Maximum number of queued messages.
#define GVIDEO_INVALID_KEY			-1						//!< Used to indicate that the request was not sucessfully processed.

/**
 *	\b Visual elements types.
 */
typedef enum {
	GVIDEO_VTYPE_SCEN_STATIC = 0,		//!< Used to static scenery.
	GVIDEO_VTYPE_SCEN_DYNAMIC,			//!< Used to dynamic scenery.
	GVIDEO_VTYPE_ELEM_STATIC,			//!< Used to static element.
	GVIDEO_VTYPE_ELEM_DYNAMIC,			//!< Used to dynamic element.
	GVIDEO_VTYPE_MAX_ELEM				//!< Used to validate valid range. MUST be the last item.
} en_visual_type;


#endif /* GVIDEO_DEFINES_HEADER */
