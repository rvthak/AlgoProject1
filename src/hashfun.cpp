#include "utils.h"
#include "hashfun.h"
#include "distributions.h"
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

#define M_VALUE (2^32-5)
#define W_VALUE 3 // in [2,6]
#define MAX_32_INT 2147483647

H::H(unsigned v_size){
	this->t = uniform_distribution(0, W_VALUE-1);
	this->w = W_VALUE;
	this->v = normal_vector(0,1,v_size);
}	

H::~H(){}

// Calculate the hash key of the given Vector
// Based on math type, slide 19 of "nnCluster.pdf"
int H::hash(Vector *p){
	return floor( (inner_product((p->vec).begin(), (p->vec).end(), (this->v).begin(), 0) + (this->t)) / (this->w) );
}

// Create the random hash functions "h" and the random values "r" and store them
G::G(int k, unsigned tableSize, unsigned v_size){
	this->M = M_VALUE;
	this->k = k;
	this->tableSize = tableSize;

	// Generate uniform random values for k "r"s
	this->r = new int[k];
	if( this->r == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for 'r' values." << endl;
		exit(1);
	}
	for(int i=0; i<k; i++){ (this->r)[i] = uniform_distribution(0, MAX_32_INT); }

	// Generate k random "h" functions
	this->h = new H[k]{v_size};
	if( this->h == nullptr ){
		cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for 'h' hash functions." << endl;
		exit(1);
	}
}

G::~G(){
	delete [] this->r;
	delete [] this->h;
}

// Calculate the hash key of the given Vector (Sum-Based)
// Based on the math type on slide 21 of "nnCluster.pdf"
int G::hash(Vector *p){
	int sum=0;
	for(int i=0; i<(this->k); i++){
		sum += mod( (this->r)[i] * (this->h)[i].hash(p) , this->M );
	}
	return mod( mod(sum, this->M) , this->tableSize );
} 

// Calculate the ID of the given Vector (Sum-Based)
int G::ID(Vector *p){
	int sum=0;
	for(int i=0; i<(this->k); i++){
		sum += mod( (this->r)[i] * (this->h)[i].hash(p) , this->M );
	}
	return mod(sum, this->M);
}
