#ifndef HASH
#define HASH

#include "bucket.h"
#include "Vector.h"
#include "hashfun.h"

// Sinple Hash Table Struct that uses randomized Hash Functions
struct HashTable{
	Bucket *bucs;	// Array of Buckets
	unsigned size;	// The amount of Buckets
	G *g;			// The Hash function used on this Hash Table

	HashTable(int k, unsigned tableSize, unsigned v_size);
	~HashTable();

	int add(Vector *vec);
};

// Multiple Hash Tables used for LSH
struct MultiHash{
	HashTable *array;	// Array containing the Hash Tables
	unsigned amount;	// The amount of Hash Tables

	MultiHash(int k, int L, unsigned tableSize, unsigned v_size);
	~MultiHash();

	void add(Vector *vec);
};

#endif
