#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS

#include "Vector.h"


// Hash Function "h"
struct H{
	std::vector<int> v;	// Vector based on Normal Distribution
	double t;			// added Slight random variation (Uniformly in [0,w) )
	unsigned w; 		// "Window" - NOT zero

	H(unsigned v_size);
	~H();
	int hash(Vector *p);
};

// Hash Function "g" (Randomized on initialization) - Calculated based on sub-hash-functions "h"
struct G{
	unsigned long M;		// Large Prime Number
	unsigned tableSize;		// The size of the TargetHash table (heuristic choice)
	unsigned k;				// The amount of "h" hash functions

	// We create both ri and hi randomly on struct init, so we need to store them
	int *r;	// The "ri" values
	H **h;	// The "hi" functions

	G(int k, unsigned tableSize, unsigned v_size);
	~G();
	int hash(Vector *p);
	int ID(Vector *p);
};

// CHRIS 01.11.2021 START

struct F {
	unsigned dimensions;
	unsigned table_size;     // The tableSize which comes from dimensions
	unsigned k;				      // The amount of "h" hash functions
	H **h; 						      // Array of h values

	F(unsigned k, unsigned dimensions, unsigned table_size);
	~F();

	int hash(Vector *p);
};

// CHRIS 01.11.2021 END

#endif
