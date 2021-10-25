#ifndef VECTOR
#define VECTOR

#include <vector>

typedef struct{
	unsigned id;
	std::vector<int> vec;
}Vector;

typedef struct{
	unsigned size;
	Vector *vecs;
}VectorArray;

VectorArray *create_VectorArray(unsigned size);
void free_VectorArray(VectorArray *vecarr);

int add_VectorArray(VectorArray *vecarr, unsigned index, int id, std::vector<int> v);

#endif