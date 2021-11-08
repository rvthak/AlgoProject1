#include "Silhouette.h"
#include "AssignedVector.h"
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

vector<float> Silhouette::generate_report_array()
{
  unsigned silhouette_average_sum;
  float silhouette_average_total;

  for (unsigned i = 0; i < this->cluster_count; i++)
  {
    float silhouette = this->generate_silhouette(i);
    silhouette_average_sum += silhouette;
    this->silhouette_array.push_back(silhouette);
  }

  silhouette_average_total = silhouette_average_sum / this->cluster_count;
  this->silhouette_array.push_back(silhouette_average_total);

  return this->silhouette_array;
}

// This method runs for n elements
// But which elements ??
float Silhouette::generate_silhouette(unsigned cluter_index)
{
  int a;    // Average distance of index to objects in same cluster
  int b;    // Average distance of index to objects in the next best (neighbor) cluster_count
  float silhouette;

  if (a < b)
    silhouette = 1 - (a / b);
  else if (a == b)
    silhouette = 0;
  else if (a > b)
    silhouette = (b / a) - 1;

  return silhouette;
}
