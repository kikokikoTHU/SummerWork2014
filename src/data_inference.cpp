#include "data_inference.h"

int edit_dist(int* mfs, int* sample, int mfs_len, int sample_len, int** detail_list)
{
	
	int max1 = sample_len;
	int max2 = mfs_len;

	int **ptr = new int*[max1 + 1];	

	for (int i=0; i<max1+1; i++) {
		ptr[i] = new int[max2 + 1];
	}

	for (int i=0; i<max1+1; i++) {
        ptr[i][0] = i;
    }

	for (int i=0; i<max2+1; i++) {
        ptr[0][i] = i;
    }

    for(int i=1; i<max1+1; i++) {
        for(int j=1 ;j<max2+1; j++) {

            int d;

            int temp = ptr[i][j-1]+1 < ptr[i-1][j]+1 ? ptr[i][j-1]+1 : ptr[i-1][j]+1;

            if(sample[i-1] == mfs[j-1]) {
                d = OK; 
            } else {
                d = ERR;
            }

			if (temp < ptr[i-1][j-1] + d) {
				detail_list[i][j] = MISS;
				ptr[i][j] = temp;
			} else {
				detail_list[i][j] = d;
				ptr[i][j] = ptr[i-1][j-1] + d;
			}
        }
    }

    int dis = ptr[max1][max2];

    for(int i = 0; i < max1 + 1; i++) {
        delete[] ptr[i];
        ptr[i] = NULL;
    }

    delete[] ptr;
    ptr = NULL;

    return dis;
}

double* initialize() {
	double* para_list = new double[4]; 

	fstream para_config_file("para_config");

	if (para_config_file) {
		para_config_file >> para_list[0];
		para_config_file >> para_list[1];
		para_config_file >> para_list[2];
		para_config_file >> para_list[3];
	} else {
		para_list[0] = 0.01;
		para_list[1] = 0.01;
		para_list[2] = 5000;
		para_list[3] = 100;
		para_config_file.open("para_config", ios::out);
		para_config_file << para_list[0] << endl;
		para_config_file << para_list[1] << endl;
		para_config_file << para_list[2] << endl;
		para_config_file << para_list[3] << endl;

		cout << "No parameter config file, default parameters are used." << endl;
	}

	para_config_file.close();

	return para_list;
}

double* inference(int* mfs, int* sample, int mfs_len, int sample_len) {
	int N = sample_len*1.01;
	int M = sample_len;

	int min_dist = sample_len*2;

	int* template_data = new int[N];
	int** detail_list = new int*[M+1];
	for (int i=0; i<M+1; i++) {
		detail_list[i] = new int[N+1];
	}

	int tmp;

	int* trace = new int[N]; 

	for (int i=0; i<mfs_len; i++) {
		generate_template_data(mfs, mfs_len, template_data, N, i);
		tmp = edit_dist(template_data, sample, N, M, detail_list);
		if (tmp < min_dist) {
			min_dist = tmp;

			int trace_i = M;
			int trace_j = N;

			for (int j=0; j<N; j++) {
				trace[N-1-j] = detail_list[trace_i][trace_j];

				if (detail_list[trace_i][trace_j] == OK  || detail_list[trace_i][trace_j] == ERR) {
					trace_i--;
					trace_j--;
				} else {
					trace_j--;
				}
			}	
		}
	}

	double* res = validation(trace, N);

	for(int i = 0; i < M + 1; i++) {
		delete[] detail_list[i];
        detail_list[i] = NULL;
    }

    delete[] detail_list;
    detail_list = NULL;

	delete[] template_data;
	template_data = NULL;

	delete[] trace;
	trace = NULL;

	return res;
}

double* validation(int* result, int result_len) {
	fstream file("truth_data");

	int truth_len;
	file >> truth_len;

	int *truth = new int[truth_len];
	for (int i=0; i<truth_len; i++) {
		file >> truth[i];
	}

	file.close();

	int alg_err = 0;
	int res_err = truth_len;

	int err_bit = 0;
	int miss_bit = 0;

	int err_recall = 0;
	int miss_recall = 0;

	int err_recall_alg = 0;
	int miss_recall_alg = 0;

	int start = 0;
	while (start < truth_len && start != MISS) 
		start++;

	for (int i=0; i<result_len; i++)
		if ((start+i) < truth_len)
			if (result[i] != truth[start+i])
				alg_err++;

	for (int i=0; i<result_len; i++)
		if (i < truth_len)
			if (result[i] == truth[i])
				res_err--;

	for (int i=0; i<truth_len; i++) {
		if (i < result_len) {
			if (truth[i] == ERR) {
				err_bit++;
				if (result[i] == ERR) {
					err_recall++;
				}
			} else if (truth[i] == MISS) {
				miss_bit++;
				if (result[i] == MISS) {
					miss_recall++;
				}
			} 
		} else {
			if (truth[i] == ERR) {
				err_bit++;
			} else if (truth[i] == MISS) {
				miss_bit++;
			} 
		}
	}
		
	for (int i=0; i<result_len; i++) {
		if ((start+i) < truth_len) {
			if (result[i] == truth[start+i])
				if (result[i] == ERR) {
					err_recall_alg++;
				} else if (result[i] == MISS) {
					miss_recall_alg;
				}
		}
	}

	double* acc = new double[6];
	acc[0] = 1.0 - (double)alg_err/(double)result_len;
	acc[1] = 1.0 - (double)res_err/(double)truth_len;
	if (err_bit == 0) {
		acc[2] = 1;
		acc[4] = 1;
	} else {
		acc[2] = (double)err_recall / (double)err_bit;
		acc[4] = (double)err_recall_alg / (double)err_bit;
	}
	if (miss_bit == 0) {
		acc[3] = 1;
		acc[5] = 1;
	} else {
		acc[3] = (double)miss_recall / (double)miss_bit;
		acc[5] = (double)miss_recall_alg / (double)miss_bit;
	}

	delete[] truth;

	return acc;
}

void experiment_1() {
	fstream file("experiment_1", ios::out);

	if (file) {
		double* acc;
		double* para_list;
		int* mfs_data;
		int* sample_data;

		para_list = initialize();

		for (int mfs_l=50; mfs_l<=300; mfs_l+=50) {
			for (int sam_l=5000; sam_l<=10000; sam_l+=1000) {
				for (int i=0; i<10; i++) {
					generate_data(para_list[0], para_list[1], sam_l, mfs_l);

					int mfs_len;
					int sample_len;
					mfs_len = read_mfs_data(mfs_data);
					sample_len = read_sample_data(sample_data);

					acc = inference(mfs_data, sample_data, mfs_len, sample_len);
					file << sam_l << " " << mfs_l << " " << acc[0] << " " << acc[1] << " " << acc[2] << " " << acc[3] << " " << acc[4] << " " << acc[5] << endl;
					cout << sam_l << " " << mfs_l << " " << acc[0] << " " << acc[1] << " " << acc[2] << " " << acc[3] << " " << acc[4] << " " << acc[5] << endl;

					delete[] mfs_data;
					mfs_data = NULL;
					delete[] sample_data;
					sample_data = NULL;
				}
			}
		}

		file.close();
	} else {
		cout << "File open error!" << endl;
	}
}	

void experiment_2() {
	fstream file("experiment_2", ios::out);

	if (file) {
		double* acc;
		double* para_list;
		int* mfs_data;
		int* sample_data;

		para_list = initialize();

		for (double miss_rate=0.002; miss_rate<=0.01; miss_rate+=0.002) {
			for (double err_rate=0.002; err_rate<=0.01; err_rate+=0.002) {
				for (int i=0; i<10; i++) {
					generate_data(miss_rate, err_rate, para_list[2], para_list[3]);

					int mfs_len;
					int sample_len;
					mfs_len = read_mfs_data(mfs_data);
					sample_len = read_sample_data(sample_data);

					acc = inference(mfs_data, sample_data, mfs_len, sample_len);
					file << miss_rate << " " << err_rate << " " 
						<< acc[0] << " " << acc[1] << " " << acc[2] << " " 
						<< acc[3] << " " << acc[4] << " " << acc[5] << endl;
					cout << miss_rate << " " << err_rate << " " 
						<< acc[0] << " " << acc[1] << " " << acc[2] << " " 
						<< acc[3] << " " << acc[4] << " " << acc[5] << endl;

					delete[] mfs_data;
					mfs_data = NULL;
					delete[] sample_data;
					sample_data = NULL;
				}
			}
		}

		file.close();
	} else {
		cout << "File open error!" << endl;
	}
}