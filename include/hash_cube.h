#ifndef HASH_CUBE
#define HASH_CUBE

#include "bucket.h"
#include "Vector.h"
#include "hashfun.h"

// Sinple Hash Table Struct that uses randomized Hash Functions
struct HashTable_Cube{
	Bucket *bucs;	// Array of Buckets
	unsigned size;	// The amount of Buckets
	G *g;			// The Hash function used on this Hash Table

	HashTable_Cube(int k, unsigned tableSize, unsigned v_size);
	~HashTable_Cube();

	int add(Vector *vec);
};

// Multiple Hash Tables used for Cube
struct MultiHash_Cube{
	HashTable_Cube *array;	// Array containing the Hash Tables
	unsigned amount;	// The amount of Hash Tables

	MultiHash_Cube(int k, int L, unsigned tableSize, unsigned v_size);
	~MultiHash_Cube();

	void add(Vector *vec);
};

#endif
