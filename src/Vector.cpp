#include "utils.h"
#include "Vector.h"
#include "shortedList.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

Vector::Vector(){ this->id = 0; }

// Prints all the data stored in a Vector
void Vector::print(){
	cout << " Id: " << this->id << endl << "   > ";
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

//------------------------------------------------------------------------------------------------------------------

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
VectorArray::~VectorArray(){ delete [] this->array; }

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
void *VectorArray::kNN_naive(Vector *query, unsigned k){

	// The naive approach to solving the k Nearest Neighbors problem is 
	// to just check all the distances and keep the shortest ones

	// We just add all the existing Vectors and their distances into a Shorted List
	// and in the end we have the k nearest Vectors stored in the list
	ShortedList *list = new ShortedList(k);
	for(unsigned i=0; i<(this->size); i++){
		list->add( &((this->array)[i]), query->l2( &((this->array)[i]) ) );
	}
	return list;
} // (!) Remember to free the returned list afterwards

//------------------------------------------------------------------------------------------------------------------

// Prints all the data stored in a Centroid
void Centroid::print(){
	for (int val: this->vec.vec){
		cout << val << ' ';
	} cout << endl;
}

// Calculate the norm between "this" and p
double Centroid::l2(Vector *p){
	int tmp;
	double sum=0;

	for(long unsigned i=0; i<(p->vec).size(); i++){
		tmp = (this->vec.vec)[i] - (p->vec)[i]; 
		sum += tmp * tmp;
	}
	return sqrt(sum);
}

// Copies the values of the given Vector to the Centroid
void Centroid::copy_Vec(Vector *p){
	// Clear the current contents
	(this->vec.vec).clear();

	// Copy the vector over
	this->vec.vec = p->vec;
}

// Assign the given vector to this Centroid
void Centroid::assign(Vector *p){
	(this->assignments).push_back(p);
	(this->cluster_size)++;
}

//------------------------------------------------------------------------------------------------------------------

CentroidArray::CentroidArray(unsigned size){
	this->array = new Centroid[size];
	this->size = size;
	this->change = true;
}

CentroidArray::~CentroidArray(){ delete [] this->array; }

// Initialize the Centroids completely randomly (May lead to bad initial state => bad clustering)
void CentroidArray::initialize_random(void *ass_vecs){
	// A vector containing the indexes of the already assigned Initial Centroid-Vectors
	std::vector<int> assigned_indexes;
	unsigned random_index;

	// Get a random Vector for each Centroid 
	for(unsigned i=0; i<(this->size); i++){

		do{
			// Get a random Vector from the AssignmentArray
			random_index = rand()%(this->size);
		// Ensure that it hasn't already been selected as a Centroid
		}while( find(assigned_indexes.begin(), assigned_indexes.end(), random_index) != assigned_indexes.end() );
		
		// Assign the Centroid
		(this->array)[i].copy_Vec( &((((AssignmentArray *)ass_vecs)->array)[random_index]) );
		
		// Add the Assigned Vector Index to a vector to avoid douplicate assignments
		assigned_indexes.push_back(random_index);
	}
}

// Use a probabilistic function to attempt to get good initial values for the Centroids
void CentroidArray::initialize_plus_plus(void *ass_vecs){

}

// Prints all the Centroids Stored
void CentroidArray::print(){
	for(unsigned i=0; i<(this->size); i++){
		(this->array)[i].print();
		cout << endl;
	}
}

// Resets all the assignments
void CentroidArray::reset_clusters(){

	for(unsigned i=0; i<(this->size); i++){
		(this->array)[i].cluster_size = 0;
		(this->array)[i].assignments.clear();
	}
}

// return 'true' if one or more assignments changed
bool CentroidArray::changed(){ return this->change; }

// Returns the index of the given Centroid-Vector or -1 if it doesnt exist
int CentroidArray::get_index(Vector *vec){
	for(unsigned i=0; i<(this->size); i++){
		if( (this->array)[i].vec.vec == vec->vec ){return i;}
	}
	return -1;
}

//------------------------------------------------------------------------------------------------------------------

// Create a AssignmentArray containing the given file contents
AssignmentArray::AssignmentArray(std::string filename){

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

	// Allocate memory to store the Centroid Pointers
	this->centroid = new Centroid *[this->size];
	if( this->centroid == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory  : " << filename << " : Failed to allocate memory for Centroid Pointers." << endl;
		exit(1);
	}

	// Allocate memory to store the distances
	this->dist = new double[this->size];
	if( this->dist == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory  : " << filename << " : Failed to allocate memory for distances." << endl;
		exit(1);
	}

	// Parse the file and store the records
	this->parse_input(filename);

	// Init the Centroid Pointers to NULL and the distances to zero
	for(unsigned i=0; i<(this->size); i++){
		(this->centroid)[i] = nullptr;
		(this->dist)[i] = 0;
	}
}

AssignmentArray::~AssignmentArray(){
	delete [] this->array;
	delete [] this->centroid;
	delete [] this->dist;
}

// Prints all the Vectors Stored in the AssignmentArray
void AssignmentArray::print(){
	for(unsigned i=0; i<(this->size); i++){
		(this->array)[i].print();
		cout << " Centroid: " << endl;
		if( (this->centroid)[i] == nullptr ){ cout << " NULL " << endl; }
		else{ (this->centroid)[i]->print(); }
		cout << " Distance: " << (this->dist)[i] << endl << endl;
	}
}

// Add a vector in the given "index" of a AssignmentArray
int AssignmentArray::add_vector(unsigned index, int id, vector<int> data){
	if( this->size < index ){ return 1; }
	this->array[index].id = id;
	this->array[index].vec = data;
	return 0;
}

// Parse the given file and load its records in the AssignmentArray
void AssignmentArray::parse_input(string filename){

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

//------------------------------------------------------------------------------------------------------------------

// < Update State > : Update Centroids

// Update the Centroid Values by calculating vector averages
void AssignmentArray::update_centroids(CentroidArray *cent){
	unsigned vec_size = (cent->array)[0].vec.vec.size();

	// For each Centroid (== for each Cluster)
	for(unsigned i=0; i<(cent->size); i++){

		std::vector<int> mean(vec_size, 0);

		// Sum all the vectors that belong to this cluster
		for(unsigned j=0; j<( (cent->array)[i].assignments.size() ); j++){
			mean = sum_vectors(&mean, &(((cent->array)[i].assignments[j])->vec) );
		}
		// And assign the new Cluster Centroid
		(cent->array)[i].vec.vec = div_vector(&mean, (cent->array)[i].assignments.size() );
	}
}
