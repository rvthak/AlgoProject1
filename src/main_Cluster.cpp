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
#define INITIAL_R 50

Centroid *exact_centroid(Vector *v, CentroidArray *cent, double *d);
void Classic_assignment(AssignmentArray *ass_vecs, CentroidArray *cent);
void Lsh_assignment(AssignmentArray *ass_vecs, MultiHash *lsh, CentroidArray *cent);
void Cube_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, int M, int k, int probes);

void reverse_range_lsh_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, unsigned index, MultiHash *lsh);
unsigned assign_list(AssignmentArray *ass_vecs, CentroidArray *cent, unsigned index, List *list);

void report_results(std::string filename, string algorithm,
	 									vector<float> silhouette_results, CentroidArray* all_centroids,
										bool complete_results);

int main(int argc, char *argv[]){
	print_header();

	// A struct to store the program parameters
	ARGS_Cluster args;
	string algorithm;

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

	// Create LSH/Cube structs if needed
	MultiHash *lsh;
	if( args.method == "LSH" ){
		// Create the LSH Structs
		lsh = new MultiHash(args.k_lsh, args.L, ass_vecs.size, (ass_vecs.array)[0].vec.size());

		// Load the input data into the structs
		lsh->loadVectors(&ass_vecs);
	}

	// While there are assignment changes
	while( cent.changed() ){

		// Make sure the clusters are empty before starting the assignments
		cent.reset_clusters(); ass_vecs.reset_clusters();

		// cout << " Assignment: " << endl;
		// < Assignment Stage > : Assign each Vector to its nearest Centroid's Cluster
		if( args.method == "Classic" )
		{
			algorithm = "Lloyds";
			Classic_assignment(&ass_vecs, &cent);
		}
		else if( args.method == "LSH" )
		{
			algorithm = "LSH Range Search";
			Lsh_assignment(&ass_vecs, lsh, &cent);
		}
		else
		{
			algorithm = "Hypercube Range Search";
			Cube_assignment(&ass_vecs, &cent, args.M, args.k_cube, args.probes);
		}

		// cout << " Update: " << endl;
		// < Update State > : Update Centroids
		ass_vecs.update_centroids(&cent);
	}

	unsigned cluster_count = args.k;
	Silhouette silhouette(cluster_count, &cent, &ass_vecs);
	vector<float> silhouette_report_array = silhouette.generate_report_array();

	print_footer();

	report_results(args.output_file, algorithm, silhouette_report_array, &cent, args.complete);

	if( args.method == "LSH" ){ delete lsh; }
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

// < Assignment > : Assign each Vector to its nearest Centroid's Cluster

// Assignment using exact approach => True Distances
void Classic_assignment(AssignmentArray *ass_vecs, CentroidArray *cent){
	double dist;
	Centroid *c;

	// For each Existing Vector
	for(unsigned i=0; i<(ass_vecs->size); i++){
		// Find the true nearest Centroid by calculating the distances to all the centroids
		c = exact_centroid( &((ass_vecs->array)[i]), cent , &dist );

		// And make the needed assignments
		c->assign( &((ass_vecs->array)[i]) );
		ass_vecs->assign( (ass_vecs->array)[i].id, c, dist );
		//cout << " Assigned: " << i << " to Centroid: " << (ass_vecs->centroid)[i] << endl;
	}
}

// Assignment using LSH => Approximate Distance
void Lsh_assignment(AssignmentArray *ass_vecs, MultiHash *lsh, CentroidArray *cent){
	double dist;
	Centroid *c;

	// For each Centroid
	for(unsigned i=0; i<(cent->size); i++){
		// Get assigned the nearest Vectors using Reverse Range Search based on the lsh struct
		reverse_range_lsh_assignment(ass_vecs, cent, i, lsh );
	}

	// Assign any Vectors left unassigned using the exact method
	for(unsigned i=0; i<(ass_vecs->size); i++){
		if( (ass_vecs->array)[i].centroid == nullptr ){
			c = exact_centroid( &((ass_vecs->array)[i]), cent , &dist );
			c->assign( &((ass_vecs->array)[i]) );
			ass_vecs->assign( (ass_vecs->array)[i].id, c, dist );
		}
	}
}

// Assignment using Hypercube => Approximate Distance
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

// Reverse Range Search using lsh
void reverse_range_lsh_assignment(AssignmentArray *ass_vecs, CentroidArray *cent, unsigned index, MultiHash *lsh){
	double R = INITIAL_R;
	unsigned assigned=1;
	List *list;

	while(assigned){
		// Search within a range for Vectors to assign to the cluster
		list = lsh->range_search( &((cent->array)[index].vec), R);

		// Assign the found Vectors to this Centroid
		assigned = assign_list(ass_vecs, cent, index, list);

		// Double the search range and search again
		R*=2;
		delete list;
	}
}

// Assign the vectors of the list to the given Centroid
// Resolves overlapping by finding the true nearest Centroid
// Returns the amount of Vectors Successfully assigned
unsigned assign_list(AssignmentArray *ass_vecs, CentroidArray *cent, unsigned index, List *list){
	unsigned count=0;
	List_node *cur = list->first;

	// For each given Vector in the list
	while( cur != nullptr ){

		// If it is not assigned to any cluster
		if( cur->data->centroid == nullptr ){

			// Assign the Vector to this cluster
			(cent->array)[index].assign(cur->data);
			ass_vecs->assign(cur->data->id, &((cent->array)[index]), (cent->array)[index].l2(cur->data) );

		}
		// If it is already assigned to another Cluster
		else if( cur->data->centroid != (&((cent->array)[index])) ){
			// Compare the true distances between the two and assign to the best one
			if( (cent->array)[index].l2(cur->data) < ((Centroid *)(cur->data->centroid))->l2(cur->data) ){
				(cent->array)[index].assign(cur->data);
				ass_vecs->assign(cur->data->id, &((cent->array)[index]), (cent->array)[index].l2(cur->data) );
			}

		}
		// Else it is already assigned to this Cluster => Do nothing

		cur = cur->next;
	}

	return count;
}


//------------------------------------------------------------------------------------------------------------------

void report_results(std::string filename, string algorithm,
	 									vector<float> silhouette_results, CentroidArray* all_centroids,
										bool complete_results)
{
	std::ofstream file;

 	// Open the output file in append mode
	file.open(filename, std::ios_base::app);

	file << "Algorithm: " << algorithm << std::endl;

	for (unsigned i = 0; i < (all_centroids->size); i++){

		file << "CLUSTER-" << i << " { size : "
		     << (all_centroids->array)[i].cluster_size << ", centroid: ";

		for(int val: (all_centroids->array)[i].vec.vec ){
			file << val << ' ';
		}
		file << std::endl;
	}

	file << "Silhouette: [ " << silhouette_results[0];

	for (unsigned k = 1; k < silhouette_results.size(); k++){
		file << ", " << silhouette_results[k] ;
	}
	file << "]" << endl << endl;

	if (complete_results == true){

		for (unsigned i = 0; i < all_centroids->size; i++)
		{
			file << "CLUSTER-" << i << " { centroid : ";

			for (unsigned k = 0; k < (all_centroids->array)[i].cluster_size; k++)
			{
				file << (all_centroids->array)[i].assignments[k]->id << ", ";
			}

			file << "}" << std::endl;
		}
	}
}