#include "hash_cube.h"
#include "shortedList.h"
#include "utils.h"
#include "Vector.h"
#include "bucket.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Create a Hash table with a randomized "g" hash function
HashTable_Cube::HashTable_Cube(int k, unsigned tableSize, unsigned v_size){

	// Allocate the Bucket Array
	this->size = tableSize;
	this->bucs = new Bucket[tableSize];
	cout << "Going to create shorted list" << endl;
	this->shorted_list = new ShortedList(0);  // TODO : ASK GIANNIS ABOUT UNSIGNED N

	if(this->bucs == nullptr)
	{
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for Bucket." << endl;
		exit(1);
	}

	if(this->shorted_list == nullptr)
	{
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for Shorted List." << endl;
		exit(1);
	}


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
	// cout << "Hash key : " << key << endl;
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

void HashTable_Cube::set_search_limits(unsigned probes, unsigned M, unsigned k)
{
	this->probes = probes;
	this->M = M;
	this->k = k;
}

int HashTable_Cube::project_query_vector(Vector* query_vector)
{
	unsigned projection_key = this->f->hash(query_vector);
	// Bucket projection_bucket = (this->bucs)[projection_key];

	cout << "Projection key : " << projection_key << endl;

	return projection_key;
}

void HashTable_Cube::analyze_query_vectors(VectorArray *query_vector_array)
{
	for(unsigned i = 0; i < (query_vector_array->size); i++)
	{
		this->project_query_vector(&((query_vector_array->array)[i]));
	}

	cout << "Analyzed all the query vectors at the cube!" << endl;
}

int HashTable_Cube::get_next_bucket_key(int last_bucket_key)
{
	vector<int> hamming_distance_limits { 5, 4, 3, 2, 1 };  // TODO : CHECK IF THIS IS CORRECT ORDER

	for (unsigned i = 0; i < hamming_distance_limits.size(); i++)
	{
		// First check for hamming distance 1, then 2 and so on
		int current_hamming_distance_limit = hamming_distance_limits.back();
		hamming_distance_limits.pop_back();

		for (unsigned j = 0; j < this->size; j++)
		{
			// Check if we have already visited that bucket
			if (find(this->visited_bucket_keys.begin(), this->visited_bucket_keys.end(), j) != this->visited_bucket_keys.end())
				continue;

			int candidate_key = j;
			int hamming_dist = hamming_distance(candidate_key, last_bucket_key);

			if (hamming_dist == current_hamming_distance_limit)
				return candidate_key;
			else
				continue;
		}
	}

	return 0;
}

void HashTable_Cube::iterate_bucket(Bucket* bucket, Vector* query_vector)
{
	Bucket_node *current_bucket_node = bucket->first;

	while (current_bucket_node != nullptr)
	{
		// Get each vector of the bucket & the L2 distance to the query vector
		Vector* vector = current_bucket_node->data;
		double distance = query_vector->l2(vector);
		this->shorted_list->add(vector, distance);
		current_bucket_node = current_bucket_node->next;
		this->vectors_searched++;
	}
}

ShortedList* HashTable_Cube::k_nearest_neighbors_search(Vector *query, std::string output)
{
	this->probes_searched = 0;
	this->vectors_searched = 0;
	this->visited_bucket_keys = vector<int>();

	unsigned max_probes = this->probes;
	unsigned max_vectors = this->M;
	unsigned k = this->k;
	int last_key = 0;

	// Look int the first projected bucket, the next buckets will be looked according to hamming distance
	int projection_key = this->project_query_vector(query);
	Bucket* projection_bucket = &(this->bucs)[projection_key];

	this->iterate_bucket(projection_bucket, query);
	last_key = projection_key;
	visited_bucket_keys.push_back(last_key);

	while ((this->probes_searched <= max_probes) && (this->vectors_searched <= max_vectors))
	{
		int current_bucket_key = get_next_bucket_key(last_key);
		Bucket* projection_bucket = &(this->bucs)[projection_key];

		this->iterate_bucket(projection_bucket, query);
		last_key = current_bucket_key;
		visited_bucket_keys.push_back(last_key);
	}

	cout << "Completed nearest neighbors search!" << endl;

	return this->shorted_list;
}

void HashTable_Cube::range_search(Vector *query, double R, std::string output)
{

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
