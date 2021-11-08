#ifndef LIST
#define LIST

#pragma once

struct Silhouette
{
  unsigned cluster_count;

  Silhouette(unsigned cluster_count);
	~Silhouette();
};

#endif
