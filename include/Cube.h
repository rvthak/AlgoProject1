#ifndef CUBE
#define CUBE

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


Cube* create_cube(int dimensions_k = DEFAULT_DIMENSIONS_K,
                  int nearest_neighbors_N = DEFAULT_NEAREST_NEIGHBORS,
                  int vectors_to_check_M = DEFAULT_VECTORS_TO_CHECK_M,
                  int probes = DEFAULT_PROBES,
                  int radious = DEFAULT_RADIOUS);

#endif
