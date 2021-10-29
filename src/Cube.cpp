#include "Cube.h"
#include "Vector.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
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

vector<int> generate_bit_array(int size)
{
  vector<int> bit_array;

  for (int i = 0; i < size; i++)
  {
    int random_int = rand() % 1;
    bit_array.push_back(random_bit);
  }

  return bit_array;
}

int convert_bit_array_to_decimal(vector<int> bit_array)
{
  int decimal;

  for (int i = 0; i < bit_array.size(); i++)
  {
    int bit = bit_array[i];
    int bit_value = bit * pow(2, i);
    decimal += bit_value;
    i++;
  }

  return decimal;
}

void process_vector(Cube* cube, Vector* vector)
{
  int one = 1;
}
