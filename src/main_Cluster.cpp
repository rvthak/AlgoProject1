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
	//ass_vecs.print();

	// Create and initialize the Cluster Centroids
	CentroidArray cent(args.k);
	cent.initialize_random(&ass_vecs);
	//cent.print();

	// While there are assignment changes
	while( ass_vecs.changed() ){

		// < Assignment Stage > : Assign each Vector to its nearest Centroid's Cluster
		if( args.method == "Classic" ){ ass_vecs.Lloyds_assignment(&cent); }
		else if( args.method == "LSH" ){ ass_vecs.Lsh_assignment(&cent, args.L, args.k_lsh); }
		else { ass_vecs.Cube_assignment(&cent, args.M, args.k_cube, args.probes); }

		// < Update State > : Update Centroids
		ass_vecs.update_centroids(&cent);
	}

	// Print Silhouette

	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------


// Silhouette Print
