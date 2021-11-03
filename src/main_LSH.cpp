#include <fstream>
#include <iostream>
#include "Args.h"
#include "List.h"
#include "utils.h"
#include "timer.h"
#include "Vector.h"
#include "hash_lsh.h"
#include "shortedList.h"


void report_results(std::string filename, unsigned id, 
	                ShortedList *lsh,   double lsh_t, 
	                ShortedList *naive, double naive_t, 
	                List *range);


int main(int argc, char *argv[]){
	bool running = true;
	print_header();

	// A struct to store the program parameters
	ARGS_LSH args;

	// Read the given terminal args (if any), and store any args you find
	args.read_terminal(argc, argv);
	args.load_defaults();
	args.print();

	// Create a Timer to time the tests
	Timer timer;
	double lsh_time, naive_time;

	// Pointers to the test results
	ShortedList *lsh_results, *naive_results;
	List *r_results;

	// Enter the main program loop
	while(running){

		// Ask for args (Asks only for "Empty" args)
		args.read_args();

		// Load both the input and query file data
		VectorArray input_vecs(args.input_file);
		VectorArray query_vecs(args.query_file);

		// Create the LSH Structs
		MultiHash lsh(args.k, args.L, getFileLines(args.input_file)/4, getFileLineLength(args.input_file)-1);

		// Load the input data into the structs
		lsh.loadVectors(&input_vecs);
		// lsh.print();
		// std::cout << " Average Vectors per Bucket: " << lsh.averageBucketSize() << std::endl;

		// For each query Vector:
		for(unsigned i=0; i<(query_vecs.size); i++){

			Vector *q = &((query_vecs.array)[i]);


			// lsh_results = lsh.kNN_lsh( q , args.k );
			// lsh_results->print();
			// delete lsh_results;

			// r_results = lsh.range_search( q , args.R );
			// r_results->print();
			// delete r_results;

			// Run and time the tests
			timer.tic();  lsh_results   = lsh.kNN_lsh( q , args.k );                            lsh_time   = timer.toc();
			timer.tic();  naive_results = (ShortedList *)(input_vecs.kNN_naive( q , args.k ));  naive_time = timer.toc();
			r_results = lsh.range_search( q , args.R );

			// Write a report on the output file
			report_results(args.output_file, q->id, lsh_results, lsh_time, naive_results, naive_time, r_results);
		
			// Results written in output file => Free the memory
			delete lsh_results; delete r_results; delete naive_results;
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
	                ShortedList *lsh, double lsh_t, 
	                ShortedList *naive, double naive_t, 
	                List *range){

	unsigned i=1;
 	std::ofstream file;

 	// Open the output file in append mode 
	file.open(filename, std::ios_base::app);

	// Write the query id
	file << "Query: " << id << std::endl;

	// Write the results for each "i-th" Neighbor found (Comparing LSH and Naive-True)
	SL_Node *lsh_p = lsh->first, *naive_p = naive->first;
	while( lsh_p != nullptr ){
		file << "Nearest neighbor-" << i++ << ": " << lsh_p->v->id << std::endl;
		file << "distanceLSH:  "  << lsh_p->dist   << std::endl;
		file << "distanceTrue: " << naive_p->dist << std::endl;

		lsh_p   = lsh_p->next;
		naive_p = naive_p->next;
	}

	// Write the test times
	file << "tLSH: "  << lsh_t   << std::endl;
	file << "tTrue: " << naive_t << std::endl;

	// Write the Range search results 
	file << "R-near neighbors:" << std::endl;
	List_node *cur = range->first;
	while( cur != nullptr ){
		file << cur->data->id << std::endl;
		cur = cur->next;
	}
  	file << std::endl;
}
