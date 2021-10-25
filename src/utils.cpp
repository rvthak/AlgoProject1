#include "utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

// Get the line count of the given file by counting the newline characters
unsigned getFileLines(string name){
	ifstream file(name);
  	return count(istreambuf_iterator<char>(file), 
                 istreambuf_iterator<char>(),'\n');
} // Returns Zero in case the file does not exits

// Get the file line width, based on the width of the first line
unsigned getFileLineLength(std::string name){
	ifstream file(name);
	string firstline;
	int tmp;
	unsigned count=0;

	// Get the first line of the file and return its length
	getline(file, firstline);

	// Turn the line into a stream for easier reading
	istringstream line_stream(firstline);

	// loop to count all the elements
	while( line_stream >> tmp ){
		count++;
	}
	
	return count;
} // Returns Zero in case the file does not exits

// Print the "UI header"
void print_header(void){
	cout << "\033[33;1m _____________________________________________________________________________________ " << endl;
	cout << "|                                                                                     |" << endl;
	cout << "|\033[0m                    \033[33;1mSoftware Development for Algorithmic Problems\033[0m                    \033[33;1m|" << endl;
	cout << "|\033[0m                             \033[33;1m1st Assignment 2021-2021\033[0m                                \033[33;1m|" << endl;
	cout << "|\033[0m                      \033[36;1mRovithakis Ioannis - Christos Tsouchlaris\033[0m                      \033[33;1m|" << endl;
	cout << "|\033[0m                              \033[36;1msdi1800164 - sdi1800204\033[0m                                \033[33;1m|" << endl;
	cout << "|_____________________________________________________________________________________|\033[0m" << endl;
	cout << endl;
}
