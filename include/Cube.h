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
  vector<bool> bit_array;
  // VectorArray property
} Cube;


Cube* create_cube(int dimensions_k,
                  int nearest_neighbors_N,
                  int vectors_to_check_M,
                  int probes,
                  int radious);

void free_cube(Cube* cube);

vector<bool> generate_bit_array(int size);

void process_vector(Cube* cube, Vector* vector);

#endif
