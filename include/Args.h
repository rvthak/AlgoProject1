#ifndef ARGS
#define ARGS

#include <string>

typedef struct{
	std::string input_file;
	std::string query_file;
	std::string output_file;
	int k;
	int L;
	int N;
	double R;
}ARGS_LSH;

ARGS_LSH *read_args_LSH(int argc, char *argv[]);
void free_args_LSH(ARGS_LSH *args);
void print_args_LSH(ARGS_LSH *args);

typedef struct{
	std::string input_file;
	std::string query_file;
	std::string output_file;
	int k;
	int M;
	int probes;
	int N;
	double R;
}ARGS_Cube;

ARGS_Cube *read_args_Cube(int argc, char *argv[]);
void free_args_Cube(ARGS_Cube *args);
void print_args_Cube(ARGS_Cube *args);

#endif