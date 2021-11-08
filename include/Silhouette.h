#ifndef LIST
#define LIST

#include "AssignedVector.h"

#pragma once

struct Silhouette
{
  AssignedVector* vector_array_clusters;  // An array that holds vector & cluster info
  unsigned cluster_count;

  Silhouette(unsigned cluster_count);
	~Silhouette();
};

#endif
