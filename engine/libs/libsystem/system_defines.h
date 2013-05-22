#ifndef ENG_SYSTEM_DEFINES_HEADER
#define ENG_SYSTEM_DEFINES_HEADER

/* Media defines. */
#define SYSTEM_COLOR_BITS 32
#define SYSTEM_MAX_X         800
#define SYSTEM_MAX_Y         600
#define SYSTEM_VMAX_X          0
#define SYSTEM_VMAX_Y          0

#define SYSTEM_DIGI_CARD     DIGI_AUTODETECT
#define SYSTEM_MIDI_CARD     MIDI_AUTODETECT


typedef enum {
	SYSTEM_RET_SUCCESS	= 0,
	SYSTEM_RET_ERROR	= -1,
} system_return_code;

#endif /* SYSTEM_DEFINES_HEADER */
