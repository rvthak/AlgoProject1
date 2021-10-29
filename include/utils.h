#ifndef UTILS
#define UTILS

#include <string>

unsigned getFileLines(std::string name);
unsigned getFileLineLength(std::string name);
bool fileExists(std::string name);

unsigned mod(int x, int y);
void clearContents(std::string filename);

bool question(std::string q);
void printStr(char *str);

void print_header(void);
void print_footer(void);

#endif