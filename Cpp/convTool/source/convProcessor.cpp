/*
 * convProcessor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */
#include "convProcessor.h"

#include <stdlib.h>
#include <string>
#include <fstream>

#include "Map1_mp.h"
#include "Mytiles_ts.h"

using namespace std;

/**************************************************************************************************/

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

	save_data(dest, "map1_data");

	free(dest.data);
}

/**************************************************************************************************/
/* Private functions.                                                                             */
/**************************************************************************************************/

void convProcessor::save_data(const st_map_data& data, const string& file_name)
{
	ofstream dest_file;
	string file_header = file_name + ".h";
	const string file_code = file_name + ".cpp";

	dest_file.open(file_header.c_str());

	/* Dump header. */
	{
		dest_file << "#ifndef ";
		dest_file << "_" << file_name << "_H" << endl;
		dest_file << nouppercase << "#define " << uppercase << "_" << file_name << "_H" << endl;

		dest_file << nouppercase << "#endif /* " << uppercase << "_" << file_name << "_H" << endl;
	}

}


