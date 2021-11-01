#ifndef CUBE
#define CUBE

#include "Vector.h"

#include <vector>

using namespace std;

typedef struct{
	int dimensions_k;
  int nearest_neighbors_N;
  int vectors_to_check_M;
  int probes;
  int radious;
  // VectorArray property
} Cube;


Cube* create_cube(int dimensions_k,
                  int nearest_neighbors_N,
                  int vectors_to_check_M,
                  int probes,
                  int radious);

void free_cube(Cube* cube);

vector<int> generate_bit_array(int size);

// int convert_bit_array_to_decimal(vector<int> bit_array);

void process_vector(Cube* cube, Vector* vector);

#endif
