/*
 * convProcessor.cpp
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */
#include "convProcessor.h"

#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "Map1_mp.h"
#include "Maze1_mp.h"
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
	//Map1_mp map1;
	Maze1_mp map1;
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

void convProcessor::save_data(const st_map_data& map, const string& file_name)
{
	ofstream dest_file;
	string file_header = file_name + ".h";
	const string file_code = file_name + ".cpp";
	const string data_type = "const unsigned short";

	/* Open header file. */
	dest_file.open(file_header.c_str());
	/* Dump header. */
	{
		string header_guard = file_name;
		transform(header_guard.begin(), header_guard.end(), header_guard.begin(), ::toupper);

		/* #ifndef _HEADER_GUARD */
		dest_file << "#ifndef _" << header_guard << "_H" << endl;
		/* #define _HEADER_GUARD */
		dest_file << "#define _" << header_guard << "_H" << endl << endl;

		dest_file << "//!< Length in members." << endl;
		dest_file << "#define " << file_name << "_len_memb " << map.lenght_memb << endl << endl;

		dest_file << "//!< Width in members." << endl;
		dest_file << "#define " << file_name << "_width_memb " << map.width_memb << endl << endl;

		dest_file << "//!< Height in members. " << endl;
		dest_file << "#define " << file_name << "_height_memb " << map.height_memb << endl << endl;

		dest_file << "/* Tiles: " << map.width_memb/4 << "x" << map.height_memb/4 << " */" << endl;
		/*extern const unsigned short file_name_map[len_memb] */
		dest_file << "extern " << data_type << " " << file_name << "_map[" << map.lenght_memb << "];" << endl << endl;

		/* #endif */
		dest_file << "#endif /* _" << header_guard << "_H" << " */" << endl;
	}
	/* Close header file. */
	dest_file.close();

	/* Open source file. */
	dest_file.open(file_code.c_str());
	/* Dump source. */
	{
		dest_file << showbase << internal << setfill('0');
		dest_file << "#include \"" << file_name << ".h\"" << endl;
		dest_file << data_type << " " << file_name << "_map[" << map.lenght_memb << "] = {" << endl;

		for (unsigned int i; i < map.lenght_memb; ++i) {

			/* Put break line. */
			if ((i%map.width_memb) == 0) {
				dest_file << endl;
			}

			dest_file << hex << setw(6) << map.data[i];

			/* Put comma. */
			if (i < (map.lenght_memb-1)) {
				dest_file << ", ";
			}
		}

		dest_file << "};" << endl;
	}
	/* Close source file. */
	dest_file.close();
}


