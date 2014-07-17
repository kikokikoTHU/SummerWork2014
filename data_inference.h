#include "data_generator.h"

double* initialize();

int best_match(int* mfs, int* sub_data, int start_pos, int N, int sub_len, int miss_len);

int find_start(int *mfs, int* sample, int sub_len, int miss_len, int N);

void inference(int* mfs, int* sample);