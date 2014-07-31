#ifndef DATA_INFERENCE_H
#define DATA_INFERENCE_H

#define OK 		0
#define ERR 	1
#define MISS 	2

#include "data_generator.h"

int edit_dist(int* mfs, int* sample, int mfs_len, int sample_len, int** detail_list);

double* initialize();

double* inference(int* mfs, int* sample, int mfs_len, int sample_len);

double* validation(int* result, int result_len);

void experiment_1();

void experiment_2();

#endif