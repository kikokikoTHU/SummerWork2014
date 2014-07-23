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

            int temp = ptr[i][j-1]+1;

            if(sample[i-1] == mfs[j-1]) {
                d = 0; 
            } else {
                d = 1;
            }

			if (temp < ptr[i-1][j-1] + d) {
				detail_list[i][j] = 2;
			} else {
				detail_list[i][j] = d;
			}

            ptr[i][j] = min(temp, ptr[i-1][j-1] + d);

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

void inference(int* mfs, int* sample) {
}

void validation() {
	
}