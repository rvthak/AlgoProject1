#include "Silhouette.h"
#include "Vector.h"
#include "shortedList.h"
#include <vector>
#include <iostream>

#define MAX_VECTORS_IN_CLUSTER 100000

using namespace std;

Silhouette::Silhouette(unsigned cluster_count, CentroidArray* all_centroids, AssignmentArray* assignment_array)
{
  this->cluster_count = cluster_count;
  this->all_centroids = all_centroids;
  this->assignment_array = assignment_array;
  this->silhouette_array = vector<float>();
}

Silhouette::~Silhouette()
{
  delete this->all_centroids;
  delete this->assignment_array;
}

// We take a centroid and
Centroid* Silhouette::get_next_cluster_centroid(Centroid* centroid)
{
  cout << "Entered get_next_cluster_centroid()" << endl;

  Centroid* next_centroid = &this->all_centroids->array[0];
  double min_distance = centroid->l2(&next_centroid->vec);

  // Add all the centroids to a shorted list so that we can retreive the next centroid
  for (unsigned i = 0; i < this->cluster_count; i++)
  {
    Centroid* other_centroid = &this->all_centroids->array[i];
    double distance = centroid->l2(&other_centroid->vec);

    if (distance < min_distance)
    {
      min_distance = distance;
      next_centroid = other_centroid;
    }
  }

  return next_centroid;
}

// We use the AssignmentArray to find all the vectors in cluster if given the centroid
VectorArray* Silhouette::get_vectors_in_cluster(Centroid* centroid)
{
  cout << "Entered get_vectors_in_cluster()" << endl;

  VectorArray* current_cluster_vectors = new VectorArray(MAX_VECTORS_IN_CLUSTER);
  unsigned current_cluster_vectors_index = 0;

  // Get the vectors for this cluster
  for (unsigned i = 0; i < this->assignment_array->size; i++)
  {
    cout << "Iteration #" << i << endl;

    Centroid* centroid_candidate = this->assignment_array->centroid[i];

    // If this check passes, the vector in the assignment array is in the examined cluster
    if (centroid_candidate == centroid)
    {
      cout << "Found the centroid in the assignment_array!" << endl;

      Vector* vector = &this->assignment_array->array[i];

      cout << "Got vector from assignment_array!" << endl;
      // double distance = this->assignment_array->dist[i];

      // cout << "Values to add :" << endl;
      // cout << "current_cluster_vectors_index : " << current_cluster_vectors_index << endl;
      // cout << "id : " << vector->id << endl;
      // cout << "vector : " << endl;
      // vector->print();

      current_cluster_vectors->add_vector(current_cluster_vectors_index, vector->id, vector->vec);

      cout << "Added vector to current_cluster_vectors!" << endl;

      current_cluster_vectors_index++;
    }
    else
    {
      continue;
    }
  }

  return current_cluster_vectors;
}

// Get the average distance of all the vectors in a cluster to their centroid
float Silhouette::get_average_distances_in_cluster(Centroid* centroid, VectorArray* cluster_vector_array)
{
  cout << "Entered get_average_distances_in_cluster()" << endl;

  double average_distance_sum;
  float average_distance;
  unsigned counter = 0;

  while (&cluster_vector_array->array[counter] != nullptr)
  {
    Vector* vector = &cluster_vector_array->array[counter];
    double distance = centroid->l2(vector);
    average_distance_sum += distance;
    counter++;
  }

  average_distance = average_distance_sum / counter;

  return average_distance;
}

// This is the method that generates the results for the output file
vector<float> Silhouette::generate_report_array()
{
  cout << "Entered generate_report_array()" << endl;

  unsigned silhouette_average_sum;
  // float silhouette_average;
  float silhouette_average_total;

  for (unsigned i = 0; i < this->cluster_count; i++)
  {
    Centroid* centroid = &this->all_centroids->array[i];
    float silhouette = this->generate_silhouette(centroid);
    silhouette_average_sum += silhouette;
    this->silhouette_array.push_back(silhouette);
  }

  silhouette_average_total = silhouette_average_sum / this->cluster_count;
  this->silhouette_array.push_back(silhouette_average_total);

  return this->silhouette_array;
}

float Silhouette::generate_silhouette(Centroid* centroid)
{
  cout << "Entered generate_silhouette()" << endl;

  VectorArray* current_cluster_vectors;
  VectorArray* next_cluster_vectors;
  Centroid* next_cluster_centroid = this->get_next_cluster_centroid(centroid);

  current_cluster_vectors = this->get_vectors_in_cluster(centroid);
  next_cluster_vectors = this->get_vectors_in_cluster(next_cluster_centroid);

  float a;    // Average distance of centroid to vectors in same cluster
  float b;    // Average distance of centroid to objects in the next best (neighbor) cluster_count
  float silhouette;

  a = this->get_average_distances_in_cluster(centroid, current_cluster_vectors);
  b = this->get_average_distances_in_cluster(centroid, next_cluster_vectors);

  if (a < b)
    silhouette = 1 - (a / b);
  else if (a == b)
    silhouette = 0;
  else if (a > b)
    silhouette = (b / a) - 1;

  return silhouette;
}
