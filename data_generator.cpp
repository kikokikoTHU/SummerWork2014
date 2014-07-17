#include "data_generator.h"

void generate_mfs_data(int N) {
	fstream file("mfs_data", ios::app);
	if (file) {
		file << N << endl;
		for (int i=0; i<N; i++) {
			file << rand()%0x1000 << endl;
		}
	} else {
		cout << "File open error!";
	}

	file.close();
}

void generate_sample_data(double p, double q, int M, int N, int* mfs_data) {
	if (q > 0.1 || p > 0.1) {
		cout << "Wrong parameters!";
		return;
	}

	fstream file("sample_data", ios::app);
	fstream file2("error_data", ios::app);

	if (file && flie2) {
		file << M << endl;

		int n = rand()%N;

		for (int i=0; i<M; i++) {
			double r = rand()/double(RAND_MAX);

			if (r < p+q && r < q) {
				file << rand()%0x1000 << endl;
				file2 << n <<endl;
			} else if (r < p+q && q <= r) {
				// receive nothing
				file << -1 << endl;
				file2 << n <<endl;
			} else if (r >= p+q) {
				file << mfs_data[n] << endl;
			}

			n++;
			if (n == N)
				n = 0;
		}
	} else {
		cout << "File open error!";
	}

	file.close();
}

int* read_mfs_data() {
	int* mfs_data;
	int N;

	fstream file("mfs_data");

	if (file) {
		file >> N >> endl;

		mfs_data = new int [N];

		for (int i=0 ; i<N; i++) {
			file >> mfs_data[i] >> endl;
		}
	} else {
		cout << "File open error" << endl;
	}

	return mfs_data;
}

int* read_sample_data() {
	int* sample_data;
	int* tmp_data;
	int M;

	fstream file("sample_data");

	if (file) {
		file >> M >> endl;

		tmp_data = new int [M];

		int count = 0;

		for (int i=0; i<M; i++) {
			file >> tmp_data[i] >> endl;
			if (tmp_data[i] != -1) {
				count++;
			}
		}

		sample_data = new int [count];

		int k = 0;

		for (int i=0; i<M; i++) {
			if (tmp_data[i] != -1) {
				sample_data[k] = tmp_data[i];
				k++;
			}
		}
	} else {
		cout << "File open error" << endl;
	}

	return sample_data;
}

void generate_data(double p, double q, int M, int N) {
	srand((unsigned)time(NULL)); 
	generate_mfs_data(N);
	int mfs_data = read_mfs_data();
	generate_sample_data(p, q, M, N, mfs_data);
}