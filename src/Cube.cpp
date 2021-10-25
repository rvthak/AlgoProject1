#include "Cube.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

Cube* create_cube(int dimensions_k,
                  int nearest_neighbors_N,
                  int vectors_to_check_M,
                  int probes,
                  int radious)
{
  Cube* cube = new Cube;

  cube->dimensions_k = dimensions_k;
  cube->nearest_neighbors_N = nearest_neighbors_N;
  cube->vectors_to_check_M = vectors_to_check_M;
  cube->probes = probes;
  cube->radious = radious;

  return cube;
}

void free_cube(Cube* cube)
{
  delete cube;
}
