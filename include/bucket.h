#ifndef BUCKET
#define BUCKET

#include "Vector.h"

// The Bucket linked list node
struct Bucket_node{
	Bucket_node *next;
	Vector *data;
	// Maybe also add ID here

	Bucket_node(Vector *v);
	~Bucket_node();
};

// Bucket of Hash Table - A simple liked list (This Struct is the head of the linked list)
struct Bucket{
	Bucket_node *first;	// Pointer to the first bucket item
	unsigned size;		// The amount of items stored in the bucket
	
	Bucket();
	~Bucket();

	int add(Vector *v);
};

#endif