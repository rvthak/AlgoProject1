#include "Silhouette.h"
#include "AssignedVector.h"
#include "shortedList.h"
#include <vector>

using namespace std;

Silhouette::Silhouette(unsigned cluster_count)
{
  this->cluster_count = cluster_count;
  this->silhouette_array = vector<float>();
}

Silhouette::~Silhouette()
{
  delete this->vector_array_clusters;
}

Vector* Silhouette::get_next_cluster_centroid(Vector* centroid, VectorArray* centroids_array)
{
  ShortedList* shorted_list = new ShortedList(this->cluster_count);

  // Add all the centroids to a shorted list so that we can retreive the next centroid
  for (unsigned i = 0; i < this->cluster_count; i++)
  {
    Vector* other_centroid = &centroids_array->array[i];
    double distance = centroid->l2(other_centroid);
    shorted_list->add(other_centroid, distance);
  }

  // We want the centroid with the smallest distance
  // That is the 1st element in the shorted list
  Vector* next_centroid = shorted_list->first->v;

  return next_centroid;
}

vector<float> Silhouette::generate_report_array(Vector* centroid, VectorArray* cluster_vector_array)
{
  unsigned silhouette_average_sum;
  float silhouette_average_total;

  for (unsigned i = 0; i < this->cluster_count; i++)
  {
    float silhouette = this->generate_silhouette(centroid);
    silhouette_average_sum += silhouette;
    this->silhouette_array.push_back(silhouette);
  }

  silhouette_average_total = silhouette_average_sum / this->cluster_count;
  this->silhouette_array.push_back(silhouette_average_total);

  return this->silhouette_array;
}

// This method runs for n elements
// But which elements ??
float Silhouette::generate_silhouette(Vector* centroid)
{
  int a;    // Average distance of centroid to vectors in same cluster
  int b;    // Average distance of centroid to objects in the next best (neighbor) cluster_count
  float silhouette;

  if (a < b)
    silhouette = 1 - (a / b);
  else if (a == b)
    silhouette = 0;
  else if (a > b)
    silhouette = (b / a) - 1;

  return silhouette;
}
