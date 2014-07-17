#include "data_inference.h"

double* initialize() {
	double* para_list = new double[4]; 

	fstream para_config_file("para_config");

	if (para_config_file) {
		file >> para_list[0] >> endl;
		file >> para_list[1] >> endl;
		file >> para_list[2] >> endl;
		file >> para_list[3] >> endl;
	} else {
		para_list[0] = 0.01;
		para_list[1] = 0.01;
		para_list[2] = 100;
		para_list[3] = 5000;
		cout << "File open error" << endl;
	}

	para_config_file.close();

	return para_list;
}

int best_match(int* mfs, int* sub_data, int start_pos, int N, int sub_len, int miss_len) {
	int error_count = 0;

	int* sub_mfs = new int[sub_len+miss_len];

	int pos = start_pos;

	for (int i=0; i<sub_len+miss_len; i++) {
		sub_mfs[i] = mfs[pos];
		pos++;
		if (pos == N)
			pos = 0;
	}

	for (int i=0; i<sub_len; i++) {
		if (sub_mfs[i] != sub_data[i])
			error_count++;
	}

	
}

int find_start(int *mfs, int* sample, int sub_len, int miss_len, int N) {
	int* sub_data = new int[sub_len];

	for (int i=0; i<sub_len; i++) {
		sub_data[i] = sample[i];
	}

	for (int i=0; i<N; i++) {

	}
}

void inference(int* mfs, int* sample) {

}