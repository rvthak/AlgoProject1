#include <iostream>
#include "Args.h"
#include "utils.h"
#include "Vector.h"
#include "parser.h"

int main(int argc, char *argv[]){
	print_header();

	// Read Args
	ARGS_LSH *args = read_args_LSH(argc,argv);
	//print_args_LSH(args);
	
	// Parse the input files
	VectorArray *input_vecs = parse_Vector_input(args->input_file);

	// Garbage collection
	free_args_LSH(args);
	free_VectorArray(input_vecs);

	return 0;
}