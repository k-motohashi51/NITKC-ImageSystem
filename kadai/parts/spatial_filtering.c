#include "spatial_filtering.h"
#include <stdio.h>

int average(imgdata* idata, int n) {
	int before[COLORNUM];	// 更新前の濃度値
	int sum[COLORNUM] = {0};
	int op;
	int N;

	// 全画素の走査
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (x == 0 && (y == 0 || y == idata->height - 1)) {
				N = 3;
			} else if (x == idata->width - 1 && (y == 0 || y == idata->height - 1)) {
				N = 3;
			} else if (x == 0 || x == idata->width - 1 || y == 0 || y == idata->height - 1) {
				N = 5;
			} else {
				N = 8;
			}


			sum[RED] = 0;
			sum[GREEN] = 0;
			sum[BLUE] = 0;
			// 近傍領域の走査
			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					// 近傍領域が画像領域外
					if (x + i < 0 || idata->width <= x + i) {
						continue;
					}

					if (y + j < 0 || idata->height <= y + j) {
						continue;
					}

					before[RED] = idata->source[RED][y + j][x + i];
					before[GREEN] = idata->source[GREEN][y + j][x + i];
					before[BLUE] = idata->source[BLUE][y + j][x + i];
					
					if (i == 0 && j == 0) {
						op = n;
					} else {
						op = 1;
					}

					sum[RED] += before[RED] * op;
					sum[GREEN] += before[GREEN] * op;
					sum[BLUE] += before[BLUE] * op;
				}
			}

			idata->results[RED][y][x] = sum[RED] / (n + N);
			idata->results[GREEN][y][x] = sum[GREEN] / (n + N);
			idata->results[BLUE][y][x] = sum[BLUE] / (n + N);
		}
	}

	return E_SUCCESS;
}

int median(imgdata* idata) {
	int N;
	double m;
	printf("height = %d\n", idata->height);

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {

			if (x == 0 && (y == 0 || y == idata->height - 1)) {
				N = 4;
			} else if (x == idata->width - 1 && (y == 0 || y == idata->height - 1)) {
				N = 4;
			} else if (x == 0 || x == idata->width - 1 || y == 0 || y == idata->height - 1) {
				N = 6;
			} else {
				N = 9;
			}

			int a[N];
			int k = 0;

			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {

					// 近傍領域が画像領域外
					if (x + i < 0 || idata->width <= x + i) {
						continue;
					}

					if (y + j < 0 || idata->height <= y + j) {
						continue;
					}

					a[k] = idata->source[RED][y + j][x + i];
					k++;
				}
			}

			// テスト表示
			printf("近傍領域：\n");
			for (int i = 0; i < N; i++) {
				printf("%d, ", a[i]);
			}
			printf("\n");

			m = calc_median(a, N);	
			printf("median = %lf\n\n", m);

			idata->results[RED][y][x] = m;
			idata->results[GREEN][y][x] = m;
			idata->results[BLUE][y][x] = m;
		}
	}

	return E_SUCCESS;
}

double calc_median(int* data, int data_num) {
	int t;
	double median;

	// 昇順にソート
	for (int i = 0; i < data_num - 1; i++) {
		for (int j = data_num - 1; j > i; j--) {
			if (data[j - 1] > data[j]) {
				t = data[j];
				data[j] = data[j - 1];
				data[j - 1] = t;
			}
		}
	}

	// テスト表示
	printf("ソート済み：");
	for (int i = 0; i < data_num; i++) {
		printf("%d, ", data[i]);
	}
	printf("\n");

	// 中央値を算出する
	if (data_num % 2 == 0) {
		printf("平均\n");
		median = (data[data_num / 2 - 1] + data[data_num / 2]) / 2.0;
	} else {
		printf("真ん中\n");
		median = data[data_num / 2];
	}


	return median;
}


int prewitt() {
	return E_SUCCESS;
}

int sobel() {
	return E_SUCCESS;
}

int laplacian() {
	return E_SUCCESS;
}

int sharpen() {
	return E_SUCCESS;
}
