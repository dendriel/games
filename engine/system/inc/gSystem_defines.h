#ifndef GSYSTEM_DEFINES_HEADER
#define GSYSTEM_DEFINES_HEADER

#define GSYSTEM_MQUEUE_NAME	"/gameSystem_queue"	//!< Queue name for gameVideo module.

/* Media defines. */
#define GAMESYSTEM_COLOR_BITS	32			//!< Screen color depth.
#define GAMESYSTEM_MAX_X		800			//!< Screen Horizontal [dimension] size.
#define GAMESYSTEM_MAX_Y		600			//!< Screen Vertical [dimension] size.
#define GAMESYSTEM_VMAX_X		0			//!< Disable virtual screen.
#define GAMESYSTEM_VMAX_Y		0			//!< Disable virtual screen.

#define GAMESYSTEM_DIGI_CARD	DIGI_AUTODETECT
#define GAMESYSTEM_MIDI_CARD	MIDI_AUTODETECT

/**
 *	\b Define modules threads identifiers.
 */
typedef enum {
	GSYSTEM_SYSTEM_TID = 0,	//!< Not used.
	GSYSTEM_BRAIN_TID,		//!< Position of brain thread id in the list.
	GSYSTEM_VIDEO_TID,		//!< Position of video thread id in the list.
	GSYSTEM_CONTROLLER_TID,	//!< Position of controller thread id in the list.
	GSYSTEM_MAX_TID			//!< List limit. Keep this as the last item!
} en_gsystem_tid;

#endif /* GSYSTEM_DEFINES_HEADER */
