#include "data_inference.h" 

void main() {
	double* para_list;
	int* mfs_data;
	int* sample_data;

	para_list = initialize();
	generate_data(para_list[0], para_list[1], para_list[2], para_list[3]);

	int mfs_len;
	int sample_len;
	mfs_len = read_mfs_data(mfs_data);
	sample_len = read_sample_data(sample_data);

	inference(mfs_data, sample_data, mfs_len, sample_len);
}