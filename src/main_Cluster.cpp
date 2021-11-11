#include <fstream>
#include <iostream>
#include "Args.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"
#include "hash_lsh.h"
#include "hash_cube.h"

using namespace std;

void Classic_assignment(AssignmentArray *ass_vecs, CentroidArray *cent);
void Lsh_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int L, int k);
void Cube_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int M, int k, int probes);

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
	while( cent.changed() ){

		// Make sure the clusters are empty before starting the assignments
		cent.reset_clusters();

		cout << " Assignment: " << endl;
		// < Assignment Stage > : Assign each Vector to its nearest Centroid's Cluster
		if( args.method == "Classic" ){ Classic_assignment(&ass_vecs, &cent); } 
		else if( args.method == "LSH" ){ Lsh_assignment(&ass_vecs, &cent, args.L, args.k_lsh); } 
		else { Cube_assignment(&ass_vecs, &cent, args.M, args.k_cube, args.probes); }

		cout << " Update: " << endl;
		// < Update State > : Update Centroids
		ass_vecs.update_centroids(&cent);
	}

	// Print Silhouette

	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

// < Assignment > : Assign each Vector to its nearest Centroid's Cluster

// Assignment using exact Lloyds with reverse range search
void Classic_assignment(AssignmentArray *ass_vecs, CentroidArray *cent){

}

// Assignment using LSH
void Lsh_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int L, int k){
	ShortedList *lsh_results;
	int index;

	// Create the LSH Structs
	MultiHash lsh(k, L, (cent->size), (cent->array)[0].vec.vec.size());
	
	// Load the input data into the structs
	lsh.loadVectors(cent);

	// For each existing Vector
	for(unsigned i=0; i<(ass_vecs->size); i++){

		// Find its nearest Centroid-Neighbor
		lsh_results = lsh.kNN_lsh( &((ass_vecs->array)[i]), 1 ); 

		// Assign the Vector to its cluster
		index = cent->get_index( lsh_results->first->v );
		(cent->array)[index].assign( lsh_results->first->v );

		delete lsh_results;
	}
}

// Assignment using Hypercube
void Cube_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int M, int k, int probes){

}

//------------------------------------------------------------------------------------------------------------------


// Silhouette Print
