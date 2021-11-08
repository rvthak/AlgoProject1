#ifndef LIST
#define LIST

#include "AssignedVector.h"
#include <vector>

#pragma once

using namespace std;

struct Silhouette
{
  AssignedVector* vector_array_clusters;  // An array that holds vector & cluster info
  vector<float> silhouette_array;         // An array of the silhouette results
  unsigned cluster_count;

  Silhouette(unsigned cluster_count);
	~Silhouette();

  Vector* get_next_cluster(Vector* query_vector, VectorArray* centroids_array);
  vector<float> generate_report_array();
  float generate_silhouette(unsigned index);
};

#endif
