#ifndef VECTOR
#define VECTOR

#include <vector>
#include <string>

// Vector Representation Struct
struct Vector{
	unsigned id;			// The Vector's Id
	std::vector<int> vec;	// The Vector Itself

	void print();	// Print the Vector Contents
};

// Array Struct Used to parse and store Vectors
struct VectorArray{
	unsigned size;	// The size of the Array == The amount of Vectors
	Vector *array;	// The Vector Storage Array itself

	VectorArray(std::string filename);
	~VectorArray();

	void print();	// Print all the Vectors of the Array

private:
	int add_vector(unsigned index, int id, std::vector<int> data);
	void parse_input(std::string filename);
};

#endif