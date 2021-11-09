#ifndef VECTOR
#define VECTOR

#include <vector>
#include <string>

// Vector Representation Struct
struct Vector{
	unsigned id;			// The Vector's Id
	std::vector<int> vec;	// The Vector Itself

	Vector();

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

//------------------------------------------------------------------------------------------------------------------

// Centroid Representation Struct
struct Centroid{
	std::vector<int> vec;	// The Centroid Itself
	unsigned cluster_size;	// The amount of Vectors Assigned on this Centroid's Cluster

	void print();				// Print the Vector Contents
	double l2(Vector *p);		// Returns the l2 norm between the two vectors
	void copy_Vec(Vector *p);	// Copies the values of the given Vector to the Centroid
};

// Array Struct Used to store Centroids
struct CentroidArray{
	unsigned size;		// The size of the Array == The amount of Centroids
	Centroid *array;	// The Centroid Storage Array itself

	CentroidArray(unsigned size);
	~CentroidArray();

	void initialize_random(void *ass_vecs);
	void initialize_plus_plus(void *ass_vecs);
	void print();
};

//------------------------------------------------------------------------------------------------------------------

// Array Struct Used to store Vector-Centroid Assignments
struct AssignmentArray{
	unsigned size;			// The size of the Array == The amount of Vectors
	Vector   *array;		// The Vector Storage Array itself
	Centroid **centroid;	// An array that stores pointers to the corresponding Centroid for each Vector 
	double   *dist;			// An array that stores the distance between the corresponding Vector and its Centroid
	
	AssignmentArray(std::string filename);
	~AssignmentArray();

	void print();	// Print all the Vector-Centroid-distance pairs

private:
	int add_vector(unsigned index, int id, std::vector<int> data);
	void parse_input(std::string filename);
};

#endif
