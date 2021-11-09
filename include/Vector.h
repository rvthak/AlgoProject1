#ifndef VECTOR
#define VECTOR

#include <vector>
#include <string>

// Vector Representation Struct
struct Vector{
	unsigned id;			// The Vector's Id
	std::vector<int> vec;	// The Vector Itself

	void print();			// Print the Vector Contents
	double l2(Vector *p);	// Returns the l2 norm between the two vectors
};

// Centroid Representation Struct
struct Centroid{
	std::vector<int> vec;	// The Centroid Itself
	unsigned cluster_size;	// The amount of Vectors Assigned on this Centroid's Cluster

	void print();			// Print the Vector Contents
	double l2(Vector *p);	// Returns the l2 norm between the two vectors
};

// Array Struct Used to parse and store Vectors
struct VectorArray{
	unsigned size;	// The size of the Array == The amount of Vectors
	Vector *array;	// The Vector Storage Array itself

	VectorArray(std::string filename);
	~VectorArray();

	void *kNN_naive(Vector *query, unsigned k);
	void print();	// Print all the Vectors of the Array

private:
	int add_vector(unsigned index, int id, std::vector<int> data);
	void parse_input(std::string filename);
};

// Array Struct Used to store Vector-Centroid Assignments
struct AssignmentArray{
	unsigned size;			// The size of the Array == The amount of Vectors
	Vector   *array;		// The Vector Storage Array itself
	Centroid **centroids;	// An array that stores the corresponding Centroid for each Vector
	double   *dist;			// An array that stores the distance between the corresponding Vector and its Centroid
	
	VectorArray(std::string filename);
	~VectorArray();

	void *kNN_naive(Vector *query, unsigned k);
	void print();	// Print all the Vectors of the Array

private:
	int add_vector(unsigned index, int id, std::vector<int> data);
	void parse_input(std::string filename);
};

#endif
