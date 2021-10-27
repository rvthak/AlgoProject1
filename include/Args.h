#ifndef ARGS
#define ARGS

#include <string>

// The values of the "Empty" struct data members
#define EMPTY_FILE  ""
#define EMPTY_INT   -1
#define EMPTY_FLOAT -1

// Argument Storage Struct for LSH
struct ARGS_LSH{
	std::string input_file, query_file, output_file;
	int k;		// Amount of LSH functions (hi) used to create the g functios
	int L;		// Amount of Hash tables used
	int N;		// Amount of Nearest Neighbors
	double R;	// Radius length

	// Initialize all args to "Empty" using an initializer list
	ARGS_LSH():input_file(EMPTY_FILE), query_file(EMPTY_FILE), output_file(EMPTY_FILE), 
	           k(EMPTY_INT), L(EMPTY_INT), N(EMPTY_INT), R(EMPTY_FLOAT){}

	void read_terminal(int argc, char *argv[]);
	void read_args();
	void load_defaults();
	void clear();
	void print();
};

// Argument Storage Struct for Cube
struct ARGS_Cube{
	std::string input_file, query_file, output_file;
	int k;		// The Projection Dimention
	int M;		// Max amount of points checked
	int probes;	// Max amount of cube vertices checked
	int N;		// Amount of Nearest Neighbors
	double R;	// Radius length

	// Initialize all args to "Empty" using an initializer list
	ARGS_Cube():input_file(EMPTY_FILE), query_file(EMPTY_FILE), output_file(EMPTY_FILE), 
	           k(EMPTY_INT), M(EMPTY_INT), probes(EMPTY_INT), N(EMPTY_INT), R(EMPTY_FLOAT){}

	void read_terminal(int argc, char *argv[]);
	void read_args();
	void load_defaults();
	void clear();
	void print();
};

#endif