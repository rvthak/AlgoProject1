#include <fstream>
#include <iostream>
#include "Args.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"
#include "hash_lsh.h"
#include "hash_cube.h"
#include "Silhouette.h"

using namespace std;

Centroid *exact_centroid(Vector *v, CentroidArray *cent, double *d);
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

	// CHRIS 12.11.21 START

	unsigned cluster_count = args.k;
	Silhouette silhouette(cluster_count, &cent, &ass_vecs);
	vector<float> silhouette_report_array = silhouette.generate_report_array();

	for (int i=0; i < silhouette_report_array.size(); i++)
	{
		cout << silhouette_report_array[i] << endl;
	}

	// CHRIS 12.11.21 END

	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

// < Assignment > : Assign each Vector to its nearest Centroid's Cluster

// Assignment using exact approach => True Distances
void Classic_assignment(AssignmentArray *ass_vecs, CentroidArray *cent){
	double dist;

	// For each Existing Vector
	for(unsigned i=0; i<(ass_vecs->size); i++){
		// Calculate the exact distances between the Vector and every Centroid
		// and return the true nearest Centroid
		(ass_vecs->centroid)[i] = exact_centroid( &((ass_vecs->array)[i]), cent , &dist );
		(ass_vecs->centroid)[i]->assign( &((ass_vecs->array)[i]) );
		(ass_vecs->dist)[i] = dist;
		//cout << " Assigned: " << i << " to Centroid: " << (ass_vecs->centroid)[i] << endl;
	}
}

// Assignment using LSH => Approximate Distance
void Lsh_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int L, int k){
	// ShortedList *lsh_results;
	// int index;

	// // Create the LSH Structs
	// MultiHash lsh(k, L, (cent->size), (cent->array)[0].vec.vec.size());

	// // Load the input data into the structs
	// lsh.loadVectors(cent);

	// // For each existing Vector
	// for(unsigned i=0; i<(ass_vecs->size); i++){

	// 	// Find its nearest Centroid-Neighbor
	// 	lsh_results = lsh.kNN_lsh( &((ass_vecs->array)[i]), 1 );

	// 	// Assign the Vector to its cluster
	// 	index = cent->get_index( lsh_results->first->v );
	// 	(cent->array)[index].assign( lsh_results->first->v );

	// 	delete lsh_results;
	// }
}

// Assignment using Hypercube
void Cube_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int M, int k, int probes){

}

//------------------------------------------------------------------------------------------------------------------

// Returns the exact nearest Centroid by calculating all the distances
Centroid *exact_centroid(Vector *v, CentroidArray *cent, double *d){
	Centroid *near;
	double min_dist, dist;

	// Set the first Centroid as the nearest for now
	near = &((cent->array)[0]);
	min_dist = v->l2( &(near->vec) );

	// For each remaining Centroid
	for(unsigned i=1; i<(cent->size); i++){
		// Calculate the Vector's exact distance
		dist = v->l2( &((cent->array)[i].vec) );

		// If it is the nearest Centroid => store it
		if( dist < min_dist ){
			min_dist = dist;
			near = &((cent->array)[i]);
		}
	}
	*d = min_dist;
	return near;
}

//------------------------------------------------------------------------------------------------------------------


// Silhouette Print
