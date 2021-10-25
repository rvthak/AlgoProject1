#ifndef CUBE
#define CUBE

#include <vector>

using namespace std;

#define DEFAULT_DIMENSIONS_K 14
#define DEFAULT_NEAREST_NEIGHBORS 1
#define DEFAULT_VECTORS_TO_CHECK_M 10
#define DEFAULT_PROBES 2
#define DEFAULT_RADIOUS 1000

typedef struct{
	int dimensions_k;
  int nearest_neighbors_N;
  int vectors_to_check_M;
  int probes;
  int radious;
} Cube;


Cube* create_cube(int dimensions_k,
                  int nearest_neighbors_N,
                  int vectors_to_check_M,
                  int probes,
                  int radious);

void free_cube(Cube* cube);

vector<bool> generate_bit_array(int size);

#endif
