#ifndef GSYSTEM_DEFINES_HEADER
#define GSYSTEM_DEFINES_HEADER

#define GAMESYSTEM_MQUEUE_NAME	"/gameSystem_queue"	//!< Queue name for gameVideo module.

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
 *	\n Keep concordance with "game_mods_names" at "modules_infos.h".
 */
typedef enum {
	GSYSTEM_SYSTEM_TH_ID = 0,	//!< Not used.
	GSYSTEM_BRAIN_TH_ID,		//!< Position of brain thread id in the list.
	GSYSTEM_VIDEO_TH_ID,		//!< Position of video thread id in the list.
	GSYSTEM_MAX_TH_ID			//!< List limit. Keep this as the last item!
} en_gSystem_th_id;

#endif /* GSYSTEM_DEFINES_HEADER */
