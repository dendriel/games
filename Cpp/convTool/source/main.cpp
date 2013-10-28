#include <iostream>
#include <string>
#include "parse_args.h"
#include "convProcessor.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Flags for options. I: input; W: array width; O: output file name [optional]
	const string flags = ":iwo";
	const string requiredFlags = "iw";
	const string help_str = "\t./convToll -i data_input_file -w data_array_width [-o data_output_file]";

	if (parse_args_counter_is_valid(argc) != true) {
		cout << "Missing parameters. Usage: " << endl;
		cout << help_str << endl;
		return -1;
	}

	vector<st_param> params = parse_args_create_list(flags);
	if (parse_args(params, argc, argv, flags.c_str()) != 0) {
		cout << "Unkown options received." << endl;
		cout << help_str << endl;
		return -1;
	}

	if (parse_args_check_flags(params, requiredFlags) != true) {
		cout << "Missing parameters." << endl;
		cout << help_str << endl;
		return -1;
	}

	convProcessor processor;
	const string input_file = parse_args_get_value(params, 'i');
	int array_width;
	(void) parse_args_get_value(params, 'w', array_width);
	const string output_file = parse_args_get_value(params, 'o');

	/* If was given the destination file name. */
	if (output_file != "") {
		processor.start(input_file, array_width, output_file);
	}
	else {
		processor.start(input_file, array_width);
	}

	return 0;
}

