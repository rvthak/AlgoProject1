#include "hash_cube.h"
#include <iostream>

using namespace std;

// Create a Hash table with a randomized "g" hash function
HashTable_Cube::HashTable_Cube(int k, unsigned tableSize, unsigned v_size){

	// Allocate the Bucket Array
	this->bucs = new Bucket[tableSize];
	if( this->bucs == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for Bucket." << endl;
		exit(1);
	}
	this->size = tableSize;

	// Create the randomized hash function
	this->g = new G{k, tableSize, v_size};
	if( this->g == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to create G hash function." << endl;
		exit(1);
	}
}

HashTable_Cube::~HashTable_Cube(){
	delete [] this->bucs;
	delete this->g;
}


// Add the given Vector to "this" Hash Table
int HashTable_Cube::add(Vector *vec){
	unsigned key = this->g->hash(vec);
	return (this->bucs)[key].add(vec);
}


// Allocate L hash tables, and set their hash functions to use k "h" sub-hash-functions
MultiHash_Cube::MultiHash_Cube(int k, int L, unsigned tableSize, unsigned v_size){

	// Allocate the Hash tables
	this->array = new HashTable[L]{k, tableSize, v_size};
	if( this->array == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for the Hash Tables." << endl;
		exit(1);
	}
	this->amount = L;
}

MultiHash_Cube::~MultiHash_Cube(){
	delete [] this->array;
}

// Add the given Vector on every Hash Table
void MultiHash_Cube::add(Vector *vec){
	for(unsigned i=0; i<this->amount; i++){
		if( (this->array)[i].add(vec) ){
			cout << "\033[31;1m (!) Fatal Error:\033[0m Hash Table Built : Failed to add Vector to Hash Table." << endl;
			exit(1);
		}
	}
}
