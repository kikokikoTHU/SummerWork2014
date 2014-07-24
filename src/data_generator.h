#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

void generate_mfs_data(int N);

void generate_sample_data(double p, double q, int M, int N, int* mfs_data);

int read_mfs_data(int* &mfs_data);

int read_sample_data(int* &visual_sample_data, int* &standard_data);

void generate_data(double p, double q, int M, int N);

void generate_template_data(int* mfs, int mfs_len, int* template_data, int template_len, int start);