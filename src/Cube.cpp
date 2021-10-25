#include "Cube.h"
#include "Vector.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

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

  cube->bit_array = generate_bit_array(cube->dimensions_k);

  return cube;
}

void free_cube(Cube* cube)
{
  delete cube;
}

vector<bool> generate_bit_array(int size)
{
  vector<bool> bit_array;

  for (int i = 0; i < size; i++)
  {
    int random_int = rand() % 1;
    bool random_bit = (random_int == 1) ? true : false;
    bit_array.push_back(random_bit);
  }

  return bit_array;
}
