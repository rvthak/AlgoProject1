#include <fstream>
#include <iostream>
#include "Args.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"

int main(int argc, char *argv[]){
	print_header();

	// A struct to store the program parameters
	ARGS_Cluster args;

	// Read the given terminal args (if any), and store any args you find
	args.read_terminal(argc, argv);
	args.load_defaults();
	args.print();

	// Load the Vectors from the Input file and store them
	AssignmentArray ass_vecs(args.input_file);
	ass_vecs.print();
	
	// Create and initialize the Cluster Centroids
	CentroidArray cent(args.k);
	cent.initialize_random(&ass_vecs);
	//cent.print();

	// Main Method loop
	// while(1){


	// 	// Assign each Vector to its nearest Centroid's Cluster


	// 	// Update Centroids


	// }

	// Print Silhouette

	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------


// Silhouette Print

