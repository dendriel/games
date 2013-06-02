#ifndef MODULES_INFOS_HEADER
#define MODULES_INFOS_HEADER

#include "game_defines.h"

typedef struct {
	int mod_id;
	const char *mod_name;
} st_game_mods;

/**
 *	\b Declare the modules names as strings.
 *	\n Keep concordance (order) with "en_gSystem_th_id" at "gSystem_defines.h".
 */
static st_game_mods game_mods_names[] = {
	{GSYSTEM_MOD_ID, "Game System"},
	{GBRAIN_MOD_ID,  "Game Brain"},
	{GVIDEO_MOD_ID,  "Game Video"},
};

/**************************************************************************************************/
/**
 *	\b Return the module name by thread ID index.
 */
#define MOD_NAME(index) (game_mods_names[index].mod_name)

#endif /* MODULES_INFOS_HEADER */
