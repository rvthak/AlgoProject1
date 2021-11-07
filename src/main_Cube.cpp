#include "Args.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"
#include "List.h"
#include "hash_cube.h"
#include "shortedList.h"
#include <iostream>
#include <fstream>

#define DIVISION_SIZE 4

// Variables Used for Performance Statistics
double ratio_sum = 0;
unsigned long count = 0;

void report_results(std::string filename, unsigned id,
	                ShortedList *hypercube_results, double hypercube_time,
	                ShortedList *naive, double naive_time,
	                List *range_results);

int main(int argc, char *argv[]){
	bool running = true;
	print_header();

	// A struct to store the program parameters
	ARGS_Cube args;

	// Create a Timer to time the tests
	Timer timer;
	double hypercube_time, naive_time;

	// Pointers to the test results
	ShortedList *hypercube_results, *naive_results;
	List *range_results;

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

		// Testing the cube structure
		Hypercube hypercube(args.k, getFileLines(args.input_file)/4, getFileLineLength(args.input_file)-1);

		hypercube.set_search_limits(args.probes, args.M, args.k);
		hypercube.loadVectors(&input_vecs);

		for(unsigned i = 0; i < (query_vecs.size); i++)
		{
			Vector *query_vector = &((query_vecs.array)[i]);
			hypercube.search_hypercube(query_vector);
			timer.tic(); hypercube_results = hypercube.k_nearest_neighbors_search(args.N);              hypercube_time = timer.toc();
			timer.tic(); naive_results = (ShortedList*)(input_vecs.kNN_naive(query_vector, args.N));  naive_time = timer.toc();
			range_results = hypercube.range_search(args.R);

			report_results(args.output_file, query_vector->id,
				 						 hypercube_results, hypercube_time,
				 						 naive_results, naive_time,
										 range_results);

			// Results written in output file => Free the memory
			delete hypercube_results; delete range_results; delete naive_results;
		}

		// Clear the old args
		args.clear();

		// Ask user if he wants to stop the program
		running = question(" Would you like to exit the program?");
	}

	print_footer();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

// Function used to Report the test results
void report_results(std::string filename, unsigned id,
	                ShortedList *hypercube_results, double hypercube_time,
	                ShortedList *naive, double naive_time,
	                List *range_results)
{
	unsigned i=1;
 	std::ofstream file;

 	// Open the output file in append mode
	file.open(filename, std::ios_base::app);

	// Write the query id
	file << "Query: " << id << std::endl;

	// Write the results for each "i-th" Neighbor found (Comparing LSH and Naive-True)
	SL_Node *hypercube_p = hypercube_results->first, *naive_p = naive->first;
	while( hypercube_p != nullptr ){
		file << "Nearest neighbor-" << i++ << ": " << hypercube_p->v->id << std::endl;
		file << "distanceHypercube:  "  << hypercube_p->dist   << std::endl;
		file << "distanceTrue: " << naive_p->dist << std::endl;

		ratio_sum += hypercube_p->dist / naive_p->dist;
		count++;

		hypercube_p   = hypercube_p->next;
		naive_p = naive_p->next;
	}

	// Write the test times
	file << "tHypercube:  "  << hypercube_time   << std::endl;
	file << "tTrue: " << naive_time << std::endl;

	// Write the Range search results
	file << "R-near neighbors:" << std::endl;
	List_node *cur = range_results->first;
	while(cur != nullptr)
	{
		file << cur->data->id << std::endl;
		cur = cur->next;
	}
  	file << std::endl;
}
