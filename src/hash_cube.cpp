#include "hash_cube.h"
#include <iostream>

using namespace std;

// Create a Hash table with a randomized "g" hash function
HashTable_Cube::HashTable_Cube(int k, unsigned tableSize, unsigned v_size){

	// Allocate the Bucket Array
	this->bucs = new Bucket[tableSize];

	if(this->bucs == nullptr)
	{
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for Bucket." << endl;
		exit(1);
	}

	this->size = tableSize;

	// Create the randomized hash function
	this->f = new F(k, v_size, tableSize);

	if(this->f == nullptr)
	{
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to create F hash function." << endl;
		exit(1);
	}

	cout << "Created hash table for cube!" << endl;
}

HashTable_Cube::~HashTable_Cube(){
	delete [] this->bucs;
	delete this->f;
}


// Add the given Vector to "this" Hash Table
int HashTable_Cube::add(Vector *vec)
{
	unsigned key = this->f->hash(vec);
	return (this->bucs)[key].add(vec, 0); // ID == 0 | We don't use ID for Cube
}

void HashTable_Cube::loadVectors(VectorArray *arr)
{
	for(unsigned i = 0; i < (arr->size); i++)
	{
		this->add(&((arr->array)[i]));
	}

	cout << "Loaded all the vectors at the cube!" << endl;
}

void project_query_vector(Vector* query_vector)
{
	unsigned projection_key = this->f->hash(query_vector);
	Bucket projection_bucket = (this->bucs)[projection_key];

}

// Allocate L hash tables, and set their hash functions to use k "h" sub-hash-functions
// MultiHash_Cube::MultiHash_Cube(int k, unsigned tableSize, unsigned v_size){
//
// 	// Allocate the Hash tables
// 	if((this->array = new HashTable_Cube*[tableSize]) == nullptr)
// 	{
// 		std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory." << std::endl;
// 		exit(1);
// 	}
// 	for(int i=0; i<L; i++)
// 	{
// 		if(((this->array)[i] = new HashTable_Cube(k, tableSize, v_size)) == nullptr)
// 		{
// 			std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory." << std::endl;
// 			exit(1);
// 		}
// 	}
//
// 	this->amount = L;
// }
//
// MultiHash_Cube::~MultiHash_Cube()
// {
// 	for(unsigned i = 0; i < (this->amount); i++)
// 	{
// 		delete (this->array)[i];
// 	}
//
// 	delete [] (this->array);
// }
//
// // Add the given Vector on every Hash Table
// void MultiHash_Cube::add(Vector *vec)
// {
// 	for(unsigned i = 0; i < this->amount; i++)
// 	{
// 		if((this->array)[i]->add(vec))
// 		{
// 			cout << "\033[31;1m (!) Fatal Error:\033[0m Hash Table Built : Failed to add Vector to Hash Table." << endl;
// 			exit(1);
// 		}
// 	}
// }
