#include <iostream>
#include "Args.h"
#include "utils.h"
#include "Vector.h"
#include "hash_cube.h"

int main(int argc, char *argv[]){
	bool running = true;
	print_header();

	// A struct to store the program parameters
	ARGS_Cube args;

	// Read the given terminal args (if any), and store any args you find
	args.read_terminal(argc, argv);
	args.load_defaults();
	args.print();

	// Enter the main program loop
	while(running){

		// Ask for args (Asks only for "Empty" args)
		args.read_args();

		// Load both the input and query file data
		VectorArray input_vecs(args.input_file);
		VectorArray query_vecs(args.query_file);



		// query_vecs.print();

		// Testing the cube structure
		HashTable_Cube cube(args.k, getFileLines(args.input_file)/4, getFileLineLength(args.input_file)-1);
		cube.loadVectors(&input_vecs);
		
		// Clear the old args
		args.clear();

		// Ask user if he wants to stop the program
		running = question(" Would you like to exit the program?");
	}

	print_footer();
	return 0;
}
