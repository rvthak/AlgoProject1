#include "hash_lsh.h"
#include "timer.h"
#include "utils.h"
#include <iostream>


// Create a Hash table with a randomized "g" hash function
HashTable::HashTable(int k, unsigned tableSize, unsigned v_size){

	// Allocate the Bucket Array
	this->bucs = new Bucket[tableSize];
	if( this->bucs == nullptr ){
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for Bucket." << std::endl;
		exit(1);
	}
	this->size = tableSize;

	// Create the randomized hash function
	this->g = new G(k, tableSize, v_size);
	if( this->g == nullptr ){
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to create G hash function." << std::endl;
		exit(1);
	}
}

HashTable::~HashTable(){
	delete [] this->bucs; 
	delete this->g;
}

// Add the given Vector to "this" Hash Table
int HashTable::add(Vector *vec){
	unsigned id = this->g->ID(vec);
	unsigned key = mod(id, g->tableSize);
	//std::cout << " KEY: " << key << ", ID: " << id << std::endl;
	return (this->bucs)[key].add(vec, id);
}

//------------------------------------------------------------------------------------------------------------------

// Allocate L hash tables, and set their hash functions to use k "h" sub-hash-functions
MultiHash::MultiHash(int k, int L, unsigned tableSize, unsigned v_size){
	// Allocate the Hash tables
	if( (this->array = new HashTable*[L]) == nullptr ){ 
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory." << std::endl;
		exit(1);
	}
	for(int i=0; i<L; i++){
		if( ((this->array)[i] = new HashTable(k, tableSize, v_size)) == nullptr ){
			std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory." << std::endl;
			exit(1);
		}
	}
	this->amount = L;
}

MultiHash::~MultiHash(){
	for(unsigned i=0; i<(this->amount); i++){
		delete (this->array)[i];
	}
	delete [] (this->array);
}

// Add the given Vector on every Hash Table
void MultiHash::add(Vector *vec){
	for(unsigned i=0; i<this->amount; i++){
		if( ((this->array)[i])->add(vec) ){
			std::cout << "\033[31;1m (!) Fatal Error:\033[0m Hash Table Built : Failed to add Vector to Hash Table." << std::endl;
			exit(1);
		}
	}
}

// Load all the Vectors of the VectorArray in the MultiHash Struct
void MultiHash::loadVectors(VectorArray *arr){
	// Add each vector to all the Hash tables
	for(unsigned i=0; i<(arr->size); i++){
		this->add( &((arr->array)[i]) );
	}
}

// LSH search for the k approximate Nearest Neighbors of the given query Vector
void MultiHash::kNN_lsh(Vector *query, std::string output){

}

// Range search for the k approximate Nearest Neighbors of the given query Vector
void MultiHash::range_search(Vector *query, double R, std::string output){

}
