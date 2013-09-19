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

using namespace std;


#include "mytiles_tileset.h"


unsigned int origin_map[] = {   0, 1, 2,
								3, 4, 5,
								6, 7, 8};

void convProcessor::start(void)
{
	// Load data from files
	// do conversion.
	// Save data to files.
	// end.

	convConversor conversor;

	st_map_data orig;
	st_map_data tileset;
	st_map_data dest;

	memset(&orig, 0, sizeof(orig));
	memset(&tileset, 0, sizeof(tileset));
	memset(&dest, 0, sizeof(dest));

	orig.uint_data = origin_map;
	orig.lenght = sizeof(origin_map)/sizeof(unsigned int);
	orig.size.w = 3;
	orig.size.h = 3;

	tileset.cushort_data = mytiles_map;
	tileset.lenght = mytiles_mapLen;
	tileset.size.w = mytiles_map_w*DATA_WIDTH;
	tileset.size.h = mytiles_map_h*DATA_WIDTH;

	conversor.convert(orig, dest, tileset);

	free(dest.ushort_data);
}
