/*
 * convProcessor.h
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#ifndef CONVPROCESSOR_H_
#define CONVPROCESSOR_H_

#include <string>
#include <vector>
#include "convConversor.h"

using namespace std;

/**
 * \brief Engine class.
 */
class convProcessor {
private:
	vector<unsigned int> m_DataMap;		//!< Loaded data from a file.

public:
	/**
	 * \brief Launch converter application.
	 * \parameter file_path Data file path.
	 * \parameter array_witdh Array width.
	 */
	void start(const string& file_path, const unsigned int& array_width);

private:
	/**
	 * \brief Save converted data into a file and with specific format (ready to be used)
	 * \parameter data The map data to be dumped in a file.
	 * \parameter file_name The name of the destination file.
	 */
	void save_data(const st_map_data& data, const string& file_name);

	/**
	 * \brief Load data array from a file.
	 * \parameter file_path The file from where to retrieve data.
	 * \return 0 if successful loaded data.
	 */
	int load_data(const string& file_path);

	/**
	 * \brief Parse a loaded line from a file.
	 */
	void parse_line(const string& line);

	/**
	 * \brief Parse and add an element to the data vector.
	 * \parameter
	 */
	void parse_memb(const string& memb);

	/**
	 * \brief Split a character array in tokens.
	 * \parameter str The string to split.
	 * \parameter c The delimiter.
	 * \note Found this functions somewhere at stackoverflow.com; will try to find out the author.
	 */
	vector<string> split(const char *str, char c = ' ');
};

#endif /* CONVPROCESSOR_H_ */
