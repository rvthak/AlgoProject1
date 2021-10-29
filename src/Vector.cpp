#include "Vector.h"
#include "utils.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Create a VectorArray containing the given file contents
VectorArray::VectorArray(string filename){

	// Get the total amount of records in the target file
	this->size = getFileLines(filename);
	if( this->size == 0 ){ 
		cout << "\033[31;1m (!) Fatal Error:\033[0m Input Parsing : " << filename << " : File empty." << endl;
		exit(1);
	}

	// Allocate memory to store the file records
	this->array = new Vector[this->size];
	if( this->array == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory  : " << filename << " : Failed to allocate memory for file records." << endl;
		exit(1);
	}

	// Parse the file and store the records
	this->parse_input(filename);
	//cout << " (i) Created VectorArray containing " << this->size << " vectors." << endl;
}

// Free a VectorArray
VectorArray::~VectorArray(){
	delete [] this->array;
}

// Add a vector in the given "index" of a VectorArray
int VectorArray::add_vector(unsigned index, int id, vector<int> data){

	if( this->size < index ){ return 1; }

	this->array[index].id = id;
	this->array[index].vec = data;

	return 0;
}

// Prints all the Vectors Stored in a VectorArray
void VectorArray::print(){
	for(unsigned i=0; i<(this->size); i++){
		(this->array)[i].print();
		cout << endl;
	}
}

// Prints all the data stored in a Vector
void Vector::print(){
	cout << " Id: " << this->id << endl;
	for (int val: this->vec){
		cout << val << ' ';
	} cout << endl;
}

// Calculate the norm between "this" and p
double Vector::l2(Vector *p){
	int tmp;
	double sum=0;

	for(long unsigned i=0; i<(p->vec).size(); i++){
		tmp = (this->vec)[i] - (p->vec)[i]; // No need for abs() since we always square the difference
		sum += tmp * tmp;
	}
	return sqrt(sum);
}

// Parse the given file and load its records in the VectorArray
void VectorArray::parse_input(string filename){

	// Amount of Integers per Vector (Does not count the Vector id)
	unsigned vec_length = getFileLineLength(filename)-1; 

	// Open the file as an ifstream
	ifstream file(filename);
	string line;

	unsigned vecs_loaded=0; // Counts the already parsed vectors 
	int val, id=-1;
	vector<int> tmp_vec;

	// For each Vector in the file (== for each line):
	while( getline(file, line) ){

		// Convert the line into a stream for easier parsing
		istringstream line_stream(line);

		// For each integer in the Vector Line:
		while( line_stream >> val ){
			// Store the first integer as the Vector Id
			if( (id==-1) && (tmp_vec.size()==0) ){ id=val; }
			else{ tmp_vec.push_back(val); }
		}

		// If you get an illegal Vector, terminate
		if( tmp_vec.size() != vec_length ){
			cout << "\033[31;1m (!) Fatal Error:\033[0m Input Parsing : " << filename << " : line no " << vecs_loaded << " : Illegal Vector." << endl;
			exit(1);
		}//cout << " Parsed Vector: Id:" << id << ", Length:" << tmp_vec.size() << endl;

		// Add the new Vector to the VectorArray Storage Array
		this->add_vector(vecs_loaded, id, tmp_vec);

		// Clear the vector contents and reset the id to "Empty", to read the next Vector
		tmp_vec.clear(); id=-1;

		// This line's Vector was loaded successfully
		vecs_loaded++; 
	}
}

// Naive search for the k Nearest Neighbors of the given query Vector
void VectorArray::kNN_naive(Vector *query, std::string output){

}
