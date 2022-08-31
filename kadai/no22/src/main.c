#include <stdio.h>
#include <stdlib.h>
#include "../inc/fourier.h"

#define CHAR_LEN 256

int main(int argc, char* argv[]) {
	FILE* fp;
	char ch;
	int N;
	complex_t* data;

	if (argc < 3) {
		printf("usage: main in22-*.txt ans22-*.txt\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("[%s] wasn't found.\n", argv[1]);
		exit(1);
	}

	fscanf(fp, "%d", &N);
	data = (complex_t*)malloc(sizeof(complex_t) * N);
	fgetc(fp);
	for (int i = 0; i < N; i++) {
		data[i].re = data[i].im = 0;
		fscanf(fp, "%lf", &data[i].re);
		ch = fgetc(fp);
		if (ch == '+' || ch == '-') {
			fscanf(fp, "%lf", &data[i].im);
			fgetc(fp);
		}
	}
	fclose(fp);

	fp = fopen(argv[2], "w");
	fprintf(fp, "j18441\n");
	DFT(data, N, fp);
	fclose(fp);

	return 0;
}
