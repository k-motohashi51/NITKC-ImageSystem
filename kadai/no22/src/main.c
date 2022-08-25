#include <stdio.h>
#include <stdlib.h>

#define CHAR_LEN 256
#define DIGIT_MAX 10

int main(int argc, char* argv[]) {
	FILE* fp;
	char ch;
	int N;
	char str[DIGIT_MAX];
	double* data;

	if (argc < 3) {
		printf("usage: main in22-*.txt ans22-*.txt\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("[%s] wasn't found.\n", argv[1]);
		exit(1);
	}

	// データ数を調べる
	for (int i = 0; i < DIGIT_MAX; i++) {
		ch = fgetc(fp);
		if (ch == ',') {
			str[i] = '\0';
			break;
		} else {
			str[i] = ch;
		}
	}
	N = atoi(str);
	data = (double*)malloc(sizeof(double) * N);

	// データを調べる
	for (int i = 0; i < N; i++) {
		ch = '\0';
		for (int j = 0; ch != ','; j++) {
			ch = fgetc(fp);
			if (ch == ',' || ch == EOF) {
				str[j] = '\0';
				break;
			} else {
				str[j] = ch;
			}
		}
		data[i] = atof(str);
	}
	fclose(fp);

	for (int i = 0; i < N; i++) {
		printf("data[%d] = %lf\n", i, data[i]);
	}

	free(data);
	
	return 0;
}
