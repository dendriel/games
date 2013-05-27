#ifndef GAMESYSTEM_DEFINES_HEADER
#define GAMESYSTEM_DEFINES_HEADER

#define GAMESYSTEM_MQUEUE_NAME	"/gameSystem_queue"	//!< Queue name for gameVideo module.

/* Media defines. */
#define GAMESYSTEM_COLOR_BITS	32			//!< Screen color depth.
#define GAMESYSTEM_MAX_X		800			//!< Screen Horizontal size.
#define GAMESYSTEM_MAX_Y		600			//!< Screen Vertical size.
#define GAMESYSTEM_VMAX_X		0			//!< Disable virtual screen.
#define GAMESYSTEM_VMAX_Y		0			//!< Disable virtual screen.

#define GAMESYSTEM_DIGI_CARD	DIGI_AUTODETECT
#define GAMESYSTEM_MIDI_CARD	MIDI_AUTODETECT

/**
 *	\b Define modules threads identifiers.
 */
typedef enum {
	GAMESYSTEM_BRAIN_TH_ID = 0,		//!< Position of brain thread id in the list.
	GAMESYSTEM_VIDEO_TH_ID,			//!< Position of video thread id in the list.
	GAMESYSTEM_MAX_TH_ID			//!< List limit. Keep this as the last item!
} en_gameSystem_th_id;

#endif /* SYSTEM_DEFINES_HEADER */
