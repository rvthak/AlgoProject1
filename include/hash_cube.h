#ifndef HASH_CUBE
#define HASH_CUBE

#include "bucket.h"
#include "Vector.h"
#include "hash_fun.h"
#include "shortedList.h"
#include <vector>

using namespace std;

// Sinple Hash Table Struct that uses randomized Hash Functions
struct HashTable_Cube{
	Bucket *bucs;	             // Array of Buckets
	ShortedList *shorted_list; // The sorted list that will help with the search
	unsigned size;	           // The amount of Buckets
	unsigned probes;           // Max amount of buckets to check
	unsigned M;                // Max amount of vectors to check
	unsigned k;                // k nearest-neighbors to check
	unsigned probes_searched;
	unsigned vectors_searched;
	vector<int> visited_bucket_keys;
	F *f;			                 // The Hash function used on this Hash Table

	HashTable_Cube(int k, unsigned tableSize, unsigned v_size);
	~HashTable_Cube();

	int add(Vector *vec);
	void loadVectors(VectorArray *arr);
	void set_search_limits(unsigned probes, unsigned M, unsigned k);
	int project_query_vector(Vector *query_vector);
	void analyze_query_vectors(VectorArray *query_vector_array);
	void iterate_bucket(Bucket* bucket, Vector* query_vector);
	int get_next_bucket_key(int last_bucket_key);
	ShortedList* k_nearest_neighbors_search(Vector *query, std::string output);
	void range_search(Vector *query, double R, std::string output);
};

// Multiple Hash Tables used for Cube
// struct MultiHash_Cube{
// 	HashTable_Cube **array;	// Array containing the Hash Tables
// 	unsigned amount;		// The amount of Hash Tables
//
// 	MultiHash_Cube(int k, unsigned tableSize, unsigned v_size);
// 	~MultiHash_Cube();
//
// 	void add(Vector *vec);
// };

#endif
