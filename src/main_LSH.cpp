#include <iostream>
#include "Args.h"
#include "utils.h"

int main(int argc, char *argv[]){
	print_header();

	// Read Args
	ARGS_LSH *args = read_args_LSH(argc,argv);
	//print_args_LSH(args);

	// Get record amount
	std::cout << " Input File lines: " << getFileLines(args->input_file) << std::endl;
	
	// Free Args
	free_args_LSH(args);

	return 0;
}