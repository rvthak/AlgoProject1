#include <iostream>
#include "Args.h"
#include "utils.h"

int main(int argc, char *argv[]){
	print_header();

	// Read Args
	ARGS_Cube *args = read_args_Cube(argc,argv);
	//print_args_Cube(args);

	// Get record amount
	std::cout << " Input File lines: " << getFileLines(args->input_file) << std::endl;
	
	// Free Args
	free_args_Cube(args);

	return 0;
}