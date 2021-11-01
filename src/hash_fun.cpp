#include "utils.h"
#include "hash_fun.h"
#include "distributions.h"
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

#define M_VALUE ((2^32)-5)
#define W_VALUE  3 // in [2,6]
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

//------------------------------------------------------------------------------------------------------------------

// Create the random hash functions "h" and the random values "r" and store them
G::G(int k, unsigned tableSize, unsigned v_size){
	this->M = M_VALUE;
	this->k = k;
	this->tableSize = tableSize;

	// Generate uniform random values for k "r"s
	this->r = new int[k];
	if( this->r == nullptr ){
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for 'r' values." << std::endl;
		exit(1);
	}
	for(int i=0; i<k; i++){ (this->r)[i] = uniform_distribution(0, MAX_32_INT); }

	// Generate k random "h" functions
	if( (this->h = new H*[k]) == nullptr ){
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for H[]." << std::endl;
		exit(1);
	}
	for(int i=0; i<k; i++){
		if( ((this->h)[i] = new H(v_size)) == nullptr ){
			std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory for Hi." << std::endl;
			exit(1);
		}
	}
}

G::~G(){
	for(unsigned i=0; i<(this->k); i++){
		delete (this->h)[i];
	}
	delete [] (this->h);
	delete [] this->r;
}

// Calculate the hash key of the given Vector (Sum-Based)
// Based on the math type on slide 21 of "nnCluster.pdf"
int G::hash(Vector *p){
	int sum=0;
	for(unsigned i=0; i<(this->k); i++){
		sum += mod( (this->r)[i] * (this->h)[i]->hash(p) , this->M );
	}
	return mod( mod(sum, this->M) , this->tableSize );
}

// Calculate the ID of the given Vector (Sum-Based)
int G::ID(Vector *p){
	int sum=0;
	for(unsigned i=0; i<(this->k); i++){
		sum += mod( (this->r)[i] * (this->h)[i]->hash(p) , this->M );
	}
	return mod(sum, this->M);
}


// CHRIS 01.11.2021 START

F::F(unsigned k, unsigned dimensions, unsigned table_size)
{
	this->dimensions = dimensions;
	this->table_size = table_size;

	// Generate k random "h" functions
	if((this->h = new H*[k]) == nullptr)
	{
		std::cout << "\033[31;1m (!) Fatal Error:\033[0m Memory : Failed to allocate memory for H[]." << std::endl;
		exit(1);
	}

	for(unsigned i = 0; i < k; i++)
	{
		if(((this->h)[i] = new H(dimensions)) == nullptr)
		{
			std::cout << "\033[31;1m (!) Fatal Error:\033[0m MultiHash Built : Failed to allocate memory for Hi." << std::endl;
			exit(1);
		}
	}

	std::cout << "Successfully created F struct with " << dimensions << " H hash functions!" << std::endl;
}

F::~F()
{
	for(unsigned i = 0; i < (this->k); i++)
	{
		delete (this->h)[i];
	}
}

int F::hash(Vector *p)
{
	int hash_key_from_array, final_hash_key;
	std::vector<int> bit_array;

	for(unsigned i = 0; i < (this->k); i++)
	{
		int h_key = (this->h)[i]->hash(p);
		int bit = generate_bit_from_h_key(h_key);
		bit_array.push_back(bit);
	}

	hash_key_from_array = convert_bit_array_to_decimal(bit_array);
	final_hash_key = hash_key_from_array % (this->table_size);

	return final_hash_key;
}

// CHRIS 01.11.2021 END
