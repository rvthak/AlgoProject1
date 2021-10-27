#ifndef UTILS
#define UTILS

#include <string>

unsigned getFileLines(std::string name);
unsigned getFileLineLength(std::string name);
bool fileExists(std::string name);

bool question(std::string q);
void printStr(char *str);

void print_header(void);
void print_footer(void);

#endif