#include <iostream>
#include <sstream>
#include <string>
#include "convProcessor.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "Missing parameters. Example: " << std::endl;
		std::cout << "\t./convToll file_path array_width" << std::endl;
		return 0;
	}

	convProcessor processor;
	const string file_path = argv[1];
	int array_width;

	std::stringstream myStream(argv[2]);
	myStream >> array_width;

	processor.start(file_path, array_width);

	return 0;
}

