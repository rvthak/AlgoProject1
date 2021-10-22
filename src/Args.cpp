#include "Args.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define VALID_ARGS_LSH  15
#define VALID_ARGS_CUBE 17

ARGS_LSH *read_args_LSH(int argc, char *argv[]){
	ARGS_LSH *args = new ARGS_LSH;

	// Check if there are enough arguments
	if( argc!=VALID_ARGS_LSH ){ exit(1); }

	// Get the argument values
	for(int i=1; i<argc; i++){

		// Check the argument flag first, then get the value
		if( strcmp(argv[i],"-i")==0 ){
			i++;
			args->input_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-q")==0){
			i++;
			args->query_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-k")==0){
			i++;
			args->k = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-L")==0){
			i++;
			args->L = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-o")==0){
			i++;
			args->output_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-N")==0){
			i++;
			args->N = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-R")==0){
			i++;
			args->R = atof(argv[i]);
		}
		// In case we dont get a known flag/string error
		else { exit(1); }
	}
	return args; // All arg parsing completed successfully
}

void free_args_LSH(ARGS_LSH *args){
	delete args;
}

void print_args_LSH(ARGS_LSH *args){
	cout << "_____________________________________________________________________________________" << endl << endl;
	cout << " input_file: " << args->input_file << endl;
	cout << " query_file: " << args->query_file << endl;
	cout << " output_file: " << args->output_file << endl;
	cout << " k: " << args->k << endl;
	cout << " L: " << args->L << endl;
	cout << " N: " << args->N << endl;
	cout << " R: " << args->R << endl;
	cout << "_____________________________________________________________________________________" << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------

ARGS_Cube *read_args_Cube(int argc, char *argv[]){
	ARGS_Cube *args = new ARGS_Cube;

	// Check if there are enough arguments
	if( argc!=VALID_ARGS_CUBE ){ exit(1); }

	// Get the argument values
	for(int i=1; i<argc; i++){

		// Check the argument flag first, then get the value
		if( strcmp(argv[i],"-i")==0 ){
			i++;
			args->input_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-q")==0){
			i++;
			args->query_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-k")==0){
			i++;
			args->k = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-M")==0){
			i++;
			args->M = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-probes")==0){
			i++;
			args->probes = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-o")==0){
			i++;
			args->output_file = string(argv[i]);
		}
		else if(strcmp(argv[i],"-N")==0){
			i++;
			args->N = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-R")==0){
			i++;
			args->R = atof(argv[i]);
		}
		// In case we dont get a known flag/string error
		else { exit(1); }
	}
	return args; // All arg parsing completed successfully
}

void free_args_Cube(ARGS_Cube *args){
	delete args;
}

void print_args_Cube(ARGS_Cube *args){
	cout << "_____________________________________________________________________________________" << endl << endl;
	cout << " input_file: " << args->input_file << endl;
	cout << " query_file: " << args->query_file << endl;
	cout << " output_file: " << args->output_file << endl;
	cout << " k: " << args->k << endl;
	cout << " M: " << args->M << endl;
	cout << " probes: " << args->probes << endl;
	cout << " N: " << args->N << endl;
	cout << " R: " << args->R << endl;
	cout << "_____________________________________________________________________________________" << endl << endl;
}