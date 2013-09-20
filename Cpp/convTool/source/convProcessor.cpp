/*
 * convProcessor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#include "convProcessor.h"
#include <stdlib.h>
#include <string.h>

#include "convConversor.h"
#include "util.h"

#include "Map1.h"
#include "mytiles_tileset.h"

using namespace std;

void convProcessor::start(void)
{
	// Load data from files
	// do conversion.
	// Save data to files.
	// end.

	convConversor conversor;
	Map1 map1;

	st_map_data dest;

	memset(&dest, 0, sizeof(dest));

	conversor.convert(map1.m_Background[0], dest);

	//for (unsigned int i = 0; i < map1.m_Background[0].width_tiles*map1.m_Background[0].height_tiles; i++) {
	//	conversor.print_tile(conversor.find_total_offset(i, dest.size_tiles.w), dest.size_tiles.w, dest.ushort_data);
	//}

	free(dest.ushort_data);
}
