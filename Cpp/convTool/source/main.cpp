#include <iostream>
#include <sstream>
#include <string>
#include "convProcessor.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cout << "Missing parameters. Example: " << std::endl;
		std::cout << "\t./convToll file_path array_width [dest_file_name]" << std::endl;
		return 0;
	}

	convProcessor processor;
	const string file_path = argv[1];
	int array_width;

	std::stringstream myStream(argv[2]);
	myStream >> array_width;

	/* If was given the destination file name. */
	if (argc > 3) {
		processor.start(file_path, array_width, argv[3]);
	}
	else {
		processor.start(file_path, array_width);
	}

	return 0;
}

