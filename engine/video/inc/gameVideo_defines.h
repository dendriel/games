#ifndef GAMEVIDEO_DEFINES_HEADER
#define GAMEVIDEO_DEFINES_HEADER

#define GAMEVIDEO_MQUEUE_NAME			"/gameVideo_queue"	//!< Queue name for gameVideo module.
#define GAMEVIDEO_SCREEN_UPDATE_US		50*1000				//!< Update the screen every 50 miliseconds.
#define GAMEVIDEO_MAX_QUEUE_MSG			1024				//!< Maximum number of queued messages.

/**
 *	\b Visual elements types.
 */
typedef enum {
	GAMEVIDEO_VTYPE_SCEN_STATIC = 0,		//!< Used to static scenery.
	GAMEVIDEO_VTYPE_SCEN_DYNAMIC,			//!< Used to dynamic scenery.
	GAMEVIDEO_VTYPE_ELEM_STATIC,			//!< Used to static element.
	GAMEVIDEO_VTYPE_ELEM_DYNAMIC,			//!< Used to dynamic element.
} en_visual_type;


#endif /* GAMEVIDEO_DEFINES_HEADER */
