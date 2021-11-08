#ifndef ASSIGNED_VECTOR
#define ASSIGNED_VECTOR

#include "Vector.h"

#pragma once

struct AssignedVector
{
  Vector* vector;
  Vector* centroid;
  double distance;     // Distance of vector to centroid

  AssignedVector(Vector* vector, Vector* centroid, double distance);
  AssignedVector();
  ~AssignedVector();
};

#endif
