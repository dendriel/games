/*
 * scenery.h
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#ifndef SCENERY_H_
#define SCENERY_H_

/**
 * Hold all scenarios.
 */
#include "GameScenery.h"
#include "Scenery01.h"

typedef enum {
	SCEN_LEVEL_NONE = -1,	//!< No level selected.
	SCEN_LEVEL0 = 0,
	SCEN_LEVEL_END			//!< No more levels. Keep it as the last!!
} en_scen_level;

//!< Postfix to increment the level.
inline en_scen_level& operator++(en_scen_level& orig, int)
{
	orig = static_cast<en_scen_level>(static_cast<int>(orig) + 1);
	return orig;
}

#endif /* SCENERY_H_ */
