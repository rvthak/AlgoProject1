#ifndef UTILS
#define UTILS

#include <string>
#include <vector>

unsigned getFileLines(std::string name);
unsigned getFileLineLength(std::string name);
bool fileExists(std::string name);

unsigned mod(int x, int y);
void clearContents(std::string filename);

bool question(std::string q);
void printStr(char *str);

void print_header(void);
void print_footer(void);

int hamming_distance(int a, int b);
int convert_bit_array_to_decimal(std::vector<int> bit_array);

#endif
