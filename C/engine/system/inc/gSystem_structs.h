#ifndef GAMESYSTEM_STRUCTS_HEADER
#define GAMESYSTEM_STRUCTS_HEADER

#include <stdbool.h>
#include "game_defines.h"

/*************************************************************************************************/
/**
 *	\b Hold game modules general informations.
 */
typedef struct {
	pthread_t tid;												//!< Module thread reference.
	const char label[GAME_MOD_LABEL_SIZE];						//!< Module reference label.
	const char mqueue[NAME_MAX];								//!< Module mqueue name.
	en_game_return_code (*mod_init)(pthread_t*, const char *);	//!< Module starting function.
	const bool execute;											//!< If the module must be started at the first gsystem iteration (maybe will be removed).
	bool initialized;											//!< If the module was successful initialized.
} st_mod_data;

#endif /* GAMESYSTEM_STRUCTS_HEADER */
