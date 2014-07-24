#include "data_generator.h"

void generate_mfs_data(int N) {
	fstream file("mfs_data", ios::out);
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

	fstream file("sample_data", ios::out);
	fstream file2("error_data", ios::out);

	if (file && file2) {
		file << M << endl;

		int n = rand()%N;

		for (int i=0; i<M; i++) {
			double r = rand()/double(RAND_MAX);

			if (r < p+q && r < q) {
				file << rand()%0x1000 << '\t' << mfs_data[n] << endl;
				//file2 << n <<endl;
			} else if (r < p+q && q <= r) {
				// receive nothing
				file << -1 << '\t' << mfs_data[n] << endl;
				//file2 << n <<endl;
			} else if (r >= p+q) {
				file << mfs_data[n] << '\t' << mfs_data[n] << endl;
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

int read_mfs_data(int* &mfs_data) {
	int N;

	fstream file("mfs_data");

	if (file) {
		file >> N;

		mfs_data = new int [N];

		for (int i=0 ; i<N; i++) {
			file >> mfs_data[i];
		}
	} else {
		cout << "File open error" << endl;
	}

	return N;
}

int read_sample_data(int* &visual_sample_data, int* &standard_data) {
	int* sample_data;
	int M;
	int len;

	fstream file("sample_data");

	if (file) {
		file >> M;

		sample_data = new int [M];
		standard_data = new int [M];

		int count = 0;

		for (int i=0; i<M; i++) {
			file >> sample_data[i] >> standard_data[i];
			if (sample_data[i] != -1) {
				count++;
			}
		}

		visual_sample_data = new int [count];

		int k = 0;

		for (int i=0; i<M; i++) {
			if (sample_data[i] != -1) {
				visual_sample_data[k] = sample_data[i];
				k++;
			}
		}

		len = count;
	} else {
		cout << "File open error" << endl;
		len = -1;
	}


	return len;
}

void generate_data(double p, double q, int M, int N) {
	srand((unsigned)time(NULL)); 
	generate_mfs_data(N);
	int *mfs_data;
	read_mfs_data(mfs_data);
	generate_sample_data(p, q, M, N, mfs_data);
}

void generate_template_data(int* mfs, int mfs_len, int* template_data, int template_len, int start) {
	int n = start;

	for (int i=0; i<template_len; i++) {
		template_data[i] = mfs[n];
		n++;
		if (n >= mfs_len)
			n = 0;
	}
}