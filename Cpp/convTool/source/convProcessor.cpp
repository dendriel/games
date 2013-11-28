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
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "Map.h"
#include "Mytiles_ts.h"
#include "Sewer_ts.h"

using namespace std;

/**************************************************************************************************/

void convProcessor::start(
		const string& file_path,
		const unsigned int& array_width,
		const string& tileset_name,
		const unsigned int& tileset_width,
		const string& output_file_name)
{

	convConversor conversor;
	Map raw_data;

	st_map_data dest;
	memset(&dest, 0, sizeof(dest));

	/* Load data map array. */
	if (this->load_data(file_path, OP_LOAD_MAP) != 0) {
		cout << "Received invalid data file path." << endl;
		return;
	}

	/* Load tileset data array. */
	if (this->load_data(file_path, OP_LOAD_TILESET) != 0) {
		cout << "Received invalid data file path." << endl;
		return;
	}

	m_Tileset.map = &m_TilesetDataMap[0];
	m_Tileset.map_width_tiles = tileset_width;

	raw_data.tiles_map = &m_DataMap[0];
	raw_data.len_tiles = m_DataMap.size();
	raw_data.width_tiles = array_width;
	raw_data.height_tiles = raw_data.len_tiles/raw_data.width_tiles;

	conversor.create_map(raw_data, dest);

	conversor.convert(raw_data, dest, m_Tileset);
/*
	for (unsigned int pos = 0; pos < raw_data.len_tiles; ++pos) {
		size_t offset = conversor.find_total_offset(pos, raw_data.width_tiles);
		cout << "offset: " << offset << "; " << dec << offset << endl;
		conversor.print_tile(offset, raw_data.width_tiles, dest.data);
	}*/

	save_data(dest, output_file_name);

	// Also must map collision domain from tile set and map object.

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
	const string raw_data_type = "const unsigned int";

	/* Open header file. */
	dest_file.open(file_header.c_str());
	/* Dump header. */
	{
		string header_guard = file_name;
		transform(header_guard.begin(), header_guard.end(), header_guard.begin(), ::toupper);

		/* #ifndef _HEADER_GUARD */
		dest_file << "#ifndef " << header_guard << "_H" << endl;
		/* #define _HEADER_GUARD */
		dest_file << "#define " << header_guard << "_H" << endl << endl;

		dest_file << "//! Length in members." << endl;
		dest_file << "#define " << file_name << "_len_memb " << map.lenght_memb << endl << endl;

		dest_file << "//! Width in members." << endl;
		dest_file << "#define " << file_name << "_width_memb " << map.width_memb << endl << endl;

		dest_file << "//! Height in members. " << endl;
		dest_file << "#define " << file_name << "_height_memb " << map.height_memb << endl << endl;

		/* extern const unsigned short file_name_map[len_memb] */
		dest_file << "extern " << data_type << " " << file_name << "_map[" << map.lenght_memb << "];" << endl << endl;

		/* extern const unsigned short file_name_map[len_memb/16] */
		dest_file << "extern " << raw_data_type << " " << file_name << "_raw[" << m_DataMap.size() << "];" << endl << endl;

		/* #endif */
		dest_file << "#endif /* " << header_guard << "_H" << " */" << endl;
	}
	/* Close header file. */
	dest_file.close();

	/* Open source file. */
	dest_file.open(file_code.c_str());
	/* Dump source. */
	{
		dest_file << showbase << internal << setfill('0');
		dest_file << "#include \"" << file_name << ".h\"" << endl;

		/* Dump map data. */
		dest_file << data_type << " " << file_name << "_map[" << map.lenght_memb << "] = {" << endl;

		for (unsigned int i = 0; i < map.lenght_memb; ++i) {

			/* Put break line. */
			if ((i%map.width_memb) == 0) {
				dest_file << endl;
			}

			dest_file << hex << setw(6) << map.data[i];

			/* Don't put comma if is the last member. */
			if (i < (map.lenght_memb-1)) {
				dest_file << ", ";
			}
		}

		dest_file << "};" << endl << endl;

		/* Dump raw map data. */
		dest_file << raw_data_type << " " << file_name << "_raw[" << dec << setw(0) << m_DataMap.size() << "] = {" << endl;
		const unsigned int *raw_vec = &m_DataMap[0];
		/* Iterate raw data vector as array. */
		for (unsigned int i = 0; i < m_DataMap.size(); ++i) {

			/* Put break line. */
			if ((i%(map.width_memb/DATA_WIDTH)) == 0) {
				dest_file << endl;
			}

			dest_file << dec << raw_vec[i];

			/* Don't put comma if is the last member. */
			if (i < (m_DataMap.size()-1)) {
				dest_file << ", ";
			}
		}
		dest_file << "};" << endl << endl;
	}
	/* Close source file. */
	dest_file.close();
}

/**************************************************************************************************/

int convProcessor::load_data(const string& file_path, en_load_op operation)
{
	string line;
	ifstream input_file;

	input_file.open(file_path.c_str());

	if (!input_file.is_open()) {
		return -1;
	}

	while (getline(input_file,line)) {
		if (operation == OP_LOAD_MAP) {
			this->parse_line(line);
		}
		/* OP_LOAD_TILESET. */
		else {
			if(this->parse_line_tileset(line) == 1) {
				/* Break if found the end of the array. */
				break;
			}
		}
	}

	input_file.close();

	return 0;
}

/**************************************************************************************************/

void convProcessor::parse_line(const string& line)
{
	/* Set when found the first bracket. */
	static bool save_memb = false;
	/* First split. */
	vector<string> splitted_line = split(line.c_str());

	/* For each token separated by spaces, do: */
	for (vector<string>::iterator iter_word = splitted_line.begin(); iter_word != splitted_line.end(); ++iter_word) {
		/* Second split, by commas. */
		vector<string> splitted_line = split((*iter_word).c_str(), ',');

		/* For each token separated by comma, do: */
		for (vector<string>::iterator iter_memb = splitted_line.begin(); iter_memb != splitted_line.end(); ++iter_memb) {
			/* Last member [?] */
			if ((*iter_memb).length() == 0) {
				continue;
			}

			/* Start copying after this member. */
			if ((*iter_memb).compare("{") == 0) {
				save_memb = true;
				continue;
			}

			if (save_memb == true) {
				this->parse_memb(*iter_memb, OP_LOAD_MAP);
			}
		}
	}
}

/**************************************************************************************************/

int convProcessor::parse_memb(const string& memb, en_load_op operation)
{
	/* Last member. */
	if ((memb.find("}") != string::npos) || (memb.find(";") != string::npos)) {

		vector<string> rec_str = split(memb.c_str(), '}');
		/* Recursive call. */

		for (vector<string>::iterator iter = rec_str.begin(); iter != rec_str.end(); ++iter) {
			/* MUST not call again for this characters, or else will start an infinite recursion. */
			if (!((*iter).compare("}")) || !((*iter).compare(";"))) {
				continue;
			}

			this->parse_memb(*iter, operation);
		}
		return 1;
	}

	/* Some of the recursive cases can fall here. */
	if (memb.size() == 0) {
		return 0;
	}

	std::stringstream myStream(memb);

	if (operation == OP_LOAD_MAP) {
		unsigned int value;
		myStream >> value;
		/* Remove map editor offset. */
		m_DataMap.push_back( (value > 0)? (value-1): value);
	}
	/* OP_LOAD_TILESET. */
	else {
		unsigned short value;
		myStream >> value;
		/* Remove map editor offset. */
		m_TilesetDataMap.push_back(value);
	}


	return 0;
}

/**************************************************************************************************/

int convProcessor::parse_line_tileset(const string& line)
{
	/* Set when found the first bracket. */
	static bool save_memb = false;
	/* First split. */
	vector<string> splitted_line = split(line.c_str());

	/* For each token separated by spaces, do: */
	for (vector<string>::const_iterator iter_word = splitted_line.begin(); iter_word != splitted_line.end(); ++iter_word) {
		/* Second split, by commas. */
		vector<string> splitted_line = split((*iter_word).c_str(), ',');

		/* For each token separated by comma, do: */
		for (vector<string>::const_iterator iter_memb = splitted_line.begin(); iter_memb != splitted_line.end(); ++iter_memb) {
			/* Last member [?] */
			if ((*iter_memb).length() == 0) {
				continue;
			}

			/* Start copying after this member. */
			if ( ((*iter_memb).compare("{") == 0) && (splitted_line.size() == 1)) {
				save_memb = true;
				continue;
			}

			if (save_memb == true) {
				if (this->parse_memb(*iter_memb, OP_LOAD_TILESET) == 1) {
					return 1;
				}
			}
		}
	}

	return 0;
}

/**************************************************************************************************/

vector<string> convProcessor::split(const char *str, char c)
{
	vector<string> result;

	do {
		const char *begin = str;

		while(*str != c && *str) {
			str++;
		}

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

