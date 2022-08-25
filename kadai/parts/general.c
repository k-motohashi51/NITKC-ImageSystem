#include <math.h>
#include <stdio.h>
#include "general.h"

// 平均値
int mean(int n, int** f, int range) {
	int sum = 0;
	int mean = 0;

	for (int j = 0; j < range; j++) {
		for (int i = 0; i < range; i++) {
			sum += f[j][i];
		}
	}

	mean = sum / n;

	return mean;
}

// 分散(σ^2)
int variance(int n, int** f, int f_mean, int range) {
	int sum = 0;
	int variance = 0;

	for (int j = 0; j < range; j++) {
		for (int i = 0; i < range; i++) {
			sum += (int)pow((f[j][i] - f_mean), 2.0);
		}
	}

	variance = sum / n;

	printf("(num, range, mean, var) = (%d, %d, %d, %d)\n", n, range, f_mean, variance);

	return variance;
}
