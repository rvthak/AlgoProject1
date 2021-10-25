#include "parser.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Parse the given input file and return its vectors stored in a VectorArray
VectorArray *parse_Vector_input(std::string filename){
	int tmp, id;

	// Get the total vector count int the file
	unsigned vec_count = getFileLines(filename);
	unsigned vec_length = getFileLineLength(filename);

	// If the file does not exist or something failed => exit
	if( vec_count==0 || vec_length==0 ){
		cout << " (!) Fatal Error: Input Parsing : " << filename << " File not found." << endl;
		exit(1);
	}
	vec_length--; // Dont count the vector id in the vector length (Decrement here to avoid underflows)
	cout << " (i) Vector count: " << vec_count << ". Vector Length: " << vec_length << endl;

	// Create the vector storage array to fit them all
	VectorArray *vecarr = create_VectorArray(vec_count);
	if( vecarr==NULL ){ 
		cout << " (!) Fatal Error: Input Parsing : " << filename << " Failed to allocate VectorArray." << endl;
		exit(1);
	}
	cout << " (i) Vector Array Created" << endl;

	// Open the given input file
	ifstream file(filename);
	if( !file.is_open() ){
		cout << " (!) Fatal Error: Input Parsing : " << filename << " Failed to open the given file." << endl;
		exit(1);
	}
	cout << " (i) File Opened" << endl;

	// For each record (line) of the input file:
	string line;
	vector<int> read_vec;
	unsigned wordCount, i;
	for(i=0; i<vec_count; i++){

		// Get the next line ( 1 line == 1 vector record)
		getline(file, line);
		//cout << "\t Got line: " << line << endl;

		// Turn the line into a stream for easier reading
		istringstream line_stream(line);

		wordCount = 0;
		while( line_stream >> tmp ){
			if( wordCount == 0 ){
				id = tmp;
				//cout << "\t\t Id: " << id << endl;
			}
			else{
				read_vec.push_back(tmp);
				//cout << " " << tmp;
			}
			wordCount++;
		}
		//cout << endl;

		// Check if the current line has the correct amount of elements
		if(( wordCount-1) != vec_length ){
			cout << " (!) Fatal Error: Input Parsing : " << filename << " Too many/Not enough numbers in record " << i+1 << ". Please fix/remove this line and try again." << endl;
			exit(1);
		}

		// Add the vector to the storage Array
		add_VectorArray(vecarr, i, id, read_vec);
	}

	cout << " TOTAL: " << i << endl;

	return vecarr;
}


