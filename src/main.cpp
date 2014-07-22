#include "data_inference.h" 

void main() {
	double* para_list;
	int* mfs_data;
	int* sample_data;

	para_list = initialize();
	generate_data(para_list[0], para_list[1], para_list[2], para_list[3]);

	mfs_data = read_mfs_data();
	sample_data = read_sample_data();

	inference();
}