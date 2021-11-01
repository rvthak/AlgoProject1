#include "utils.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Get the line count of the given file by counting the newline characters
unsigned getFileLines(string name){
	ifstream file(name);
  	return count(istreambuf_iterator<char>(file),
                 istreambuf_iterator<char>(),'\n');
} // Returns Zero in case the file does not exits

// Get the file line width, based on the width of the first line
unsigned getFileLineLength(string name){
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

// Check if a given file exists
bool fileExists(string name){
    ifstream file(name.c_str());
    return file.good();
}

// Get a binary answer to the given question
bool question(string q){
	cout << "\033[36;1m (?) Question : \033[0m" << q << " : (y/n)" << endl;

	string str;
	while(1){
		cout << "     ";
		cin >> str;

		if (cin.fail()){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\033[36;1m (?) Invalid input :\033[0m Try again : (y/n)" << endl;
		}
		else if(str=="y"){
			cin.get();
			return true;
		}
		else if(str=="n"){
			cin.get();
			return false;
		}
		else{
			cout << "\033[36;1m (?) Invalid input :\033[0m Try again : (y/n)" << endl;
		}
	}
}

// Modulo : Always positive
unsigned mod(int x, int y){
	if( x<0 ){ x*=(-1); }
	if( y<0 ){ y*=(-1); }
	return x%y;
}

// Open the given if (if it exists) and clear all of its existing contents
void clearContents(string filename){
	fopen(filename.c_str(), "w");
}

// Prints the chars of the string independently
void printStr(char *str){
	int i=0;
	while( str[i] != 0){
		printf("%c", str[i]);
		i++;
	} printf("\n");
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

// Print the "UI foooter"
void print_footer(void){
	cout << "\033[33;1m _____________________________________________________________________________________ " << endl;
	cout << "|                                                                                     |" << endl;
	cout << "|\033[0m                                \033[36;1m Shutting Down\033[0m                                       \033[33;1m|" << endl;
	cout << "|_____________________________________________________________________________________|\033[0m" << endl;
	cout << endl;
}

// Calculates the hamming distance between two given integers
int hamming_distance(int a, int b)
{
	int x = a ^ b;
	int distance = 0;

	while (x > 0)
	{
		distance += x & 1;
		x >>= 1;
  }

	return distance;
}

int convert_bit_array_to_decimal(std::vector<int> bit_array)
{
  int decimal;

  for (long unsigned i = 0; i < bit_array.size(); i++)
  {
    int bit = bit_array[i];
    int bit_value = bit * pow(2, i);
    decimal += bit_value;
    i++;
  }

  return decimal;
}

int generate_bit_from_h_key(int h_key)
{
	int bit = (h_key % 2 == 0) ? 1 : 0;
	return bit;
}
