#ifndef MACROS_HEADER
#define MACROS_HEADER

#include "game_defines.h"
#include "debug.h"

/**************************************************************************************************/
/**
 *	\b Return GAME_RET_UNITIALIZED if validation is false.
 */
#define CHECK_INITIALIZED(flag) if (!flag) {error("Sub-module not initialized."); return GAME_RET_UNINITIALIZED;}

#endif /* MACROS_HEADER */
