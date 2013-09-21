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

#include "Map1_mp.h"
#include "Mytiles_ts.h"

using namespace std;

void convProcessor::start(void)
{
	// Load data from files
	// do conversion.
	// Save data to files.
	// end.

	convConversor conversor;
	Map1_mp map1;
	Mytiles_ts mytiles_ts;

	st_map_data dest;
	memset(&dest, 0, sizeof(dest));

	conversor.create_map(map1, dest);

	conversor.convert(map1, dest, mytiles_ts);

	for (unsigned int pos = 0; pos < map1.len_tiles; ++pos) {
		size_t offset = conversor.find_total_offset(pos, map1.width_tiles);
		cout << "offset: " << offset << endl;
		conversor.print_tile(offset, map1.width_tiles, dest.data);
	}

	free(dest.data);
}
