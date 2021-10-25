#include "Vector.h"

VectorArray *create_VectorArray(unsigned size){
	VectorArray *vecarr = new VectorArray;
	vecarr->vecs = new Vector[size];
	vecarr->size = size;
	return vecarr;
}

void free_VectorArray(VectorArray *vecarr){
	delete vecarr->vecs;
	delete vecarr;
}


int add_VectorArray(VectorArray *vecarr, unsigned index, int id, std::vector<int> v){

	if( vecarr->size < index ){ return 1; }

	vecarr->vecs[index].id = id;
	vecarr->vecs[index].vec = v;

	return 0;
}