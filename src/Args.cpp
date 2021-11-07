#include "Args.h"
#include "utils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

void read_arg(string name){

	cout << "\033[33;1m (i) User Input:\033[0m Please input '" << name << "' value and press enter:" << endl << "     ";
}

void arg_file_exists(string name, string file){
	if( !fileExists(file) ){
		cout << "\033[31;1m (!) Input Error:\033[0m : " << name << " : File '" << file << "' does not exits" << endl;
		exit(1);
	}
}

void error_arg(string name){
	cout << "\033[31;1m (!) Input Error:\033[0m Invalid '" << name << "' value" << endl;
	exit(1);
}

//------------------------------------------------------------------------------------------------------------------

#define LSH_DEFAULT_K 4
#define LSH_DEFAULT_L 5
#define LSH_DEFAULT_N 1
#define LSH_DEFAULT_R 10000

// Read any given iitial terminal arguments and store them
void ARGS_LSH::read_terminal(int argc, char *argv[]){

	// Get the argument values
	for(int i=1; i<argc; i++){

		// Check the argument flag first, then get the value
		if( strcmp(argv[i],"-i")==0 ){
			i++;
			this->input_file = string(argv[i]);
			arg_file_exists("input_file", this->input_file);
		}
		else if(strcmp(argv[i],"-q")==0){
			i++;
			this->query_file = string(argv[i]);
			arg_file_exists("query_file", this->query_file);
		}
		else if(strcmp(argv[i],"-k")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->k ){}
			else{ error_arg("k"); }
		}
		else if(strcmp(argv[i],"-L")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->L ){}
			else{ error_arg("L"); }
		}
		else if(strcmp(argv[i],"-o")==0){
			i++;
			this->output_file = string(argv[i]);
			// We do not check if the output file exists or not
			// We just clear any existing contents
			clearContents(this->output_file);
		}
		else if(strcmp(argv[i],"-N")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->N ){}
			else{ error_arg("N"); }
		}
		else if(strcmp(argv[i],"-R")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->R ){}
			else{ error_arg("R"); }
		}
		// In case we dont get a known flag/string error
		else {
			cout <<"\033[31;1m (!) Fatal Error:\033[0m Arg parsing : Unknown arg " << argv[i] << endl;
			exit(1); 
		}
	}
}

// Fill "Empty" args with default values where possible
void ARGS_LSH::load_defaults(){
	if( this->k == EMPTY_INT ){   this->k = LSH_DEFAULT_K; }
	if( this->L == EMPTY_INT ){   this->L = LSH_DEFAULT_L; }
	if( this->N == EMPTY_INT ){   this->N = LSH_DEFAULT_N; }
	if( this->R == EMPTY_FLOAT ){ this->R = LSH_DEFAULT_R; }
}

// Ask the user for input on any currently "Empty" args
void ARGS_LSH::read_args(){

	// Check if any arg is "Empty" and ask the user to fill it

	if( this->input_file == EMPTY_FILE ){
		read_arg("input_file");
		if( cin >> this->input_file ){
			arg_file_exists("input_file", this->input_file);
		}
		else{ error_arg("input_file"); }
	}
	if( this->query_file == EMPTY_FILE ){
		read_arg("query_file");
		if( cin >> this->query_file ){
			arg_file_exists("query_file", this->query_file);
		}
		else{ error_arg("query_file"); }
	}
	if( this->output_file == EMPTY_FILE ){
		read_arg("output_file");
		if( cin >> this->output_file ){
			// We do not check if the output file exists or not
			// We just clear any existing contents
			clearContents(this->output_file);
		}
		else{ error_arg("output_file"); }
	}

	if( this->k == EMPTY_INT ){
		read_arg("k");
		if( cin >> this->k ){}
		else{ error_arg("k"); }
	}
	if( this->L == EMPTY_INT ){
		read_arg("L");
		if( cin >> this->L ){}
		else{ error_arg("L"); }
	}
	if( this->N == EMPTY_INT ){
		read_arg("N");
		if( cin >> this->N ){}
		else{ error_arg("N"); }
	}

	if( this->R == EMPTY_FLOAT ){
		read_arg("R");
		if( cin >> this->R ){}
		else{ error_arg("R"); }
	}
}

// Set the args to "Empty"
void ARGS_LSH::clear(){
	this->input_file = EMPTY_FILE;
	this->query_file = EMPTY_FILE;
	this->output_file = EMPTY_FILE;

	this->k = EMPTY_INT;
	this->L = EMPTY_INT;
	this->N = EMPTY_INT;

	this->R = EMPTY_FLOAT;
}

// Print the curent args
void ARGS_LSH::print(){
	cout << "\033[33;1m _____________________________________________________________________________________\033[0m"  << endl;
	cout << "\033[33;1m|                                                                                     |\033[0m" << endl;
	printf( "\033[33;1m| input_file: \033[0m %-70s \033[33;1m|\033[0m\n", (this->input_file).c_str());
	printf( "\033[33;1m| query_file: \033[0m %-70s \033[33;1m|\033[0m\n", (this->query_file).c_str());
	printf( "\033[33;1m| output_file: \033[0m%-70s \033[33;1m|\033[0m\n", (this->output_file).c_str());
	printf( "\033[33;1m| k: \033[0m%-80d \033[33;1m|\033[0m\n", this->k);
	printf( "\033[33;1m| L: \033[0m%-80d \033[33;1m|\033[0m\n", this->L);
	printf( "\033[33;1m| N: \033[0m%-80d \033[33;1m|\033[0m\n", this->N);
	printf( "\033[33;1m| R: \033[0m%-80.2f \033[33;1m|\033[0m\n", this->R);
	cout << "\033[33;1m|_____________________________________________________________________________________|\033[0m" << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------

#define CUBE_DEFAULT_K 14
#define CUBE_DEFAULT_M 10
#define CUBE_DEFAULT_PROBES 2
#define CUBE_DEFAULT_N 1
#define CUBE_DEFAULT_R 10000

// Read any given iitial terminal arguments and store them
void ARGS_Cube::read_terminal(int argc, char *argv[]){

	// Get the argument values
	for(int i=1; i<argc; i++){

		// Check the argument flag first, then get the value
		if( strcmp(argv[i],"-i")==0 ){
			i++;
			this->input_file = string(argv[i]);
			arg_file_exists("input_file", this->input_file);
		}
		else if(strcmp(argv[i],"-q")==0){
			i++;
			this->query_file = string(argv[i]);
			arg_file_exists("query_file", this->query_file);
		}
		else if(strcmp(argv[i],"-k")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->k ){}
			else{ error_arg("k"); }
		}
		else if(strcmp(argv[i],"-M")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->M ){}
			else{ error_arg("M"); }
		}
		else if(strcmp(argv[i],"-probes")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->probes ){}
			else{ error_arg("probes"); }
		}
		else if(strcmp(argv[i],"-o")==0){
			i++;
			this->output_file = string(argv[i]);
			// We do not check if the output file exists or not
			// We just clear any existing contents
			clearContents(this->output_file);
		}
		else if(strcmp(argv[i],"-N")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->N ){}
			else{ error_arg("N"); }
		}
		else if(strcmp(argv[i],"-R")==0){
			i++;
			stringstream ss(argv[i]);
			if( ss >> this->R ){}
			else{ error_arg("R"); }
		}
		// In case we dont get a known flag/string error
		else {
			cout <<"\033[31;1m (!) Fatal Error:\033[0m Arg parsing : Unknown arg " << argv[i] << endl;
			exit(1); 
		}
	}
}

// Fill "Empty" args with default values where possible
void ARGS_Cube::load_defaults(){
	if( this->k == EMPTY_INT ){ 	 this->k = CUBE_DEFAULT_K; }
	if( this->M == EMPTY_INT ){ 	 this->M = CUBE_DEFAULT_M; }
	if( this->probes == EMPTY_INT ){ this->probes = CUBE_DEFAULT_PROBES; }
	if( this->N == EMPTY_INT ){ 	 this->N = CUBE_DEFAULT_N; }
	if( this->R == EMPTY_FLOAT ){ 	 this->R = CUBE_DEFAULT_R; }
}

// Ask the user for input on any currently "Empty" args
void ARGS_Cube::read_args(){

	// Check if any arg is "Empty" and ask the user to fill it

	if( this->input_file == EMPTY_FILE ){
		read_arg("input_file");
		if( cin >> this->input_file ){
			arg_file_exists("input_file", this->input_file);
		}
		else{ error_arg("input_file"); }
	}
	if( this->query_file == EMPTY_FILE ){
		read_arg("query_file");
		if( cin >> this->query_file ){
			arg_file_exists("query_file", this->query_file);
		}
		else{ error_arg("query_file"); }
	}
	if( this->output_file == EMPTY_FILE ){
		read_arg("output_file");
		if( cin >> this->output_file ){
			// We do not check if the output file exists or not
			// We just clear any existing contents
			clearContents(this->output_file);
		}
		else{ error_arg("output_file"); }
	}

	if( this->k == EMPTY_INT ){
		read_arg("k");
		if( cin >> this->k ){}
		else{ error_arg("k"); }
	}
	if( this->M == EMPTY_INT ){
		read_arg("M");
		if( cin >> this->M ){}
		else{ error_arg("M"); }
	}
	if( this->probes == EMPTY_INT ){
		read_arg("probes");
		if( cin >> this->probes ){}
		else{ error_arg("probes"); }
	}
	if( this->N == EMPTY_INT ){
		read_arg("N");
		if( cin >> this->N ){}
		else{ error_arg("N"); }
	}

	if( this->R == EMPTY_FLOAT ){
		read_arg("R");
		if( cin >> this->R ){}
		else{ error_arg("R"); }
	}
}

// Set the args to "Empty"
void ARGS_Cube::clear(){
	this->input_file = EMPTY_FILE;
	this->query_file = EMPTY_FILE;
	this->output_file = EMPTY_FILE;

	this->k = EMPTY_INT;
	this->M = EMPTY_INT;
	this->probes = EMPTY_INT;
	this->N = EMPTY_INT;

	this->R = EMPTY_FLOAT;
}

// Print the curent args
void ARGS_Cube::print(){

	cout << "\033[33;1m _____________________________________________________________________________________\033[0m"  << endl;
	cout << "\033[33;1m|                                                                                     |\033[0m" << endl;
	printf( "\033[33;1m| input_file: \033[0m %-70s \033[33;1m|\033[0m\n", (this->input_file).c_str());
	printf( "\033[33;1m| query_file: \033[0m %-70s \033[33;1m|\033[0m\n", (this->query_file).c_str());
	printf( "\033[33;1m| output_file: \033[0m%-70s \033[33;1m|\033[0m\n", (this->output_file).c_str());
	printf( "\033[33;1m| k: \033[0m%-80d \033[33;1m|\033[0m\n", this->k);
	printf( "\033[33;1m| M: \033[0m%-80d \033[33;1m|\033[0m\n", this->M);
	printf( "\033[33;1m| probes: \033[0m%-75d \033[33;1m|\033[0m\n", this->probes);
	printf( "\033[33;1m| N: \033[0m%-80d \033[33;1m|\033[0m\n", this->N);
	printf( "\033[33;1m| R: \033[0m%-80.2f \033[33;1m|\033[0m\n", this->R);
	cout << "\033[33;1m|_____________________________________________________________________________________|\033[0m" << endl << endl;
}
