#include "Silhouette.h"


Silhouette::Silhouette(unsigned cluster_count)
{
  this->cluster_count = cluster_count;
}

Silhouette::~Silhouette()
{

}

// This method runs for n elements
// But which elements ??
float Silhouette::generate_result_silhouette(unsigned index)
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
