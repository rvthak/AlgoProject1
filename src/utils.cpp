#include "utils.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
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
unsigned long mod(double x, double y){
	if( x<0 ){ x*=(-1); }
	if( y<0 ){ y*=(-1); }
	return (unsigned long)std::fmod(x,y);
}

// Open the given if (if it exists) and clear all of its existing contents
void clearContents(string filename){
	std::ofstream file;
	file.open(filename, std::ofstream::out | std::ofstream::trunc);
	file.close();
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

// Print the Distance Divergence
void print_avg_divergence(double div){
	std::cout << "\033[33;1m (i) Average Distance Divergence: \033[0m" << div << std::endl;
}

// Print the total time
void print_time(double time){
	std::cout << "\033[33;1m (i) Total Execution Time: \033[0m" << time << " sec" << std::endl << std::endl;
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


// We get a bit array and we convert it to it's decimal value
// f.e. { 0, 1, 1, 0, 1 } == 20
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

// When we get a hash key from an H hash function, we generate a bit
int generate_bit_from_h_key(int h_key)
{
	int bit = (h_key % 2 == 0) ? 1 : 0;
	return bit;
}

// Calculate the dot product between the two given vectors
double dot_product(std::vector<int> x, std::vector<double> y){
	if( x.size() != y.size() ){ return 0; }

	unsigned size = x.size();
	double sum = 0;

	for(unsigned i=0; i<size; i++){
		sum += (double)(x[i]) * y[i];
	}
	return sum;
}

// Add the two vectors element to element
std::vector<int> sum_vectors(std::vector<int> *x, std::vector<int> *y){
	std::vector<int> sum;
	for(unsigned i=0; i<(x->size()); i++){
		sum.push_back( (*x)[i] + (*y)[i] );
	}
	return sum;
}

// Divide all the elements of 'x' by 'd'
std::vector<int> div_vector(std::vector<int> *x, unsigned d){
	std::vector<int> div;
	for(unsigned i=0; i<(x->size()); i++){
		div.push_back( (*x)[i] / d );
	}
	return div;
}
