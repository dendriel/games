/*
 * convProcessor.h
 *
 *  Created on: 17/09/2013
 *      Author: vitor
 */

#ifndef CONVPROCESSOR_H_
#define CONVPROCESSOR_H_

#include <string>
#include "convConversor.h"

using namespace std;

/**
 * \brief Engine class.
 */
class convProcessor {

public:
	/**
	 * \brief Launch converter application
	 */
	void start(void);

private:
	/**
	 * \brief Save converted data into a file and with specific format (ready to be used)
	 * \parameter data The map data to be dumped in a file.
	 * \parameter file_name The name of the destination file.
	 */
	void save_data(const st_map_data& data, const string& file_name);
};

#endif /* CONVPROCESSOR_H_ */
