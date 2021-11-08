#include "AssignedVector.h"
#include "Vector.h"


AssignedVector::AssignedVector(Vector* vector, Vector* centroid, double distance)
{
  this->vector = vector;
  this->centroid = centroid;
  this->distance = distance;
}


AssignedVector::AssignedVector()
{

}

AssignedVector::~AssignedVector()
{
  delete this->vector;
  delete this->centroid;
}
