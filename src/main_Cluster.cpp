#include <fstream>
#include <iostream>
#include "Args.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"

int main(int argc, char *argv[]){
	bool running = true;
	print_header();

	// A struct to store the program parameters
	ARGS_Cluster args;

	// Read the given terminal args (if any), and store any args you find
	args.read_terminal(argc, argv);
	args.load_defaults();
	args.print();


	Centroid cent[10];

	// Initialization++
	


	// Main Method loop




	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------


// Silhouette Print

