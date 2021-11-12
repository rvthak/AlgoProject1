#ifndef SILHOUETTE
#define SILHOUETTE

#include "Vector.h"
#include <vector>

using namespace std;

struct Silhouette
{
  CentroidArray* all_centroids;           // An array that holds all the centroids
  AssignmentArray* assignment_array;      // An array that holds ALL vector & cluster info
  vector<float> silhouette_array;         // An array of the silhouette results
  unsigned cluster_count;

  Silhouette(unsigned cluster_count, CentroidArray* all_centroids, AssignmentArray* assignment_array);
	~Silhouette();

  Centroid* get_next_cluster_centroid(Centroid* centroid);
  VectorArray* get_vectors_in_cluster(Centroid* centroid);
  float get_average_distances_in_cluster(Centroid* centroid, VectorArray* cluster_vector_array);
  vector<float> generate_report_array();
  float generate_silhouette(Centroid* centroid);
};

#endif
