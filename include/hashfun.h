#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS

#include <vector>
#include "Vector.h"

// Hash Function "h"
struct H{
	std::vector<int> v;	// Vector based on Normal Distribution
	double t;			// added Slight random variation (Uniformly in [0,w) )
	unsigned w; 		// "Window" - NOT zero

	H();
	~H();
	int hash(Vector *p);
};

// Hash Function "g" (Randomized on initialization) - Calculated based on sub-hash-functions "h"
struct G{
	unsigned M;				// Large Prime Number
	unsigned tableSize;		// The size of the TargetHash table (heuristic choice)
	unsigned k;				// The amount of "h" hash functions

	// We create both ri and hi randomly on struct init, so we need to store them
	int *r;	 // An array storing the "ri" values
	H *h;	 // An array storing the "hi" functions

	G(int k, unsigned tableSize, unsigned v_size);
	~G();
	int hash(Vector *p);
	int ID(Vector *p);
};

#endif