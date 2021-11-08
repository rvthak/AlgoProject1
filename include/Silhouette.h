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

  Vector* get_next_cluster_centroid(Vector* centroid, VectorArray* centroids_array);        // TODO : CHANGE THIS TO CLUSTER DATA STRUCTURE
  vector<float> generate_report_array(Vector* centroid, VectorArray* cluster_vector_array); // TODO : CHANGE THIS TO CLUSTER DATA STRUCTURE
  float generate_silhouette(Vector* centroid);
};

#endif
