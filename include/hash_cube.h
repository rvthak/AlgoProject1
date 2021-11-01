#ifndef HASH_CUBE
#define HASH_CUBE

#include "bucket.h"
#include "Vector.h"
#include "hash_fun.h"

// Sinple Hash Table Struct that uses randomized Hash Functions
struct HashTable_Cube{
	Bucket *bucs;	// Array of Buckets
	unsigned size;	// The amount of Buckets
	F *f;			// The Hash function used on this Hash Table

	HashTable_Cube(int k, unsigned tableSize, unsigned v_size);
	~HashTable_Cube();

	int add(Vector *vec);
	void loadVectors(VectorArray *arr);
	void project_query_vector(Vector* query_vector);
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
