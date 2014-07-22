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

            if(str1[i-1] == str2[j-1]) {
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
		file >> para_list[0] >> endl;
		file >> para_list[1] >> endl;
		file >> para_list[2] >> endl;
		file >> para_list[3] >> endl;
	} else {
		para_list[0] = 0.01;
		para_list[1] = 0.01;
		para_list[2] = 5000;
		para_list[3] = 100;
		cout << "File open error" << endl;
	}

	para_config_file.close();

	return para_list;
}

void inference(int* mfs, int* sample) {
}