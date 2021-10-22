#include "utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Get the line count of the given file by counting the newline characters
unsigned getFileLines(string name){
	ifstream file(name); 
  	return count(istreambuf_iterator<char>(file), 
                 istreambuf_iterator<char>(),'\n');
}

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
