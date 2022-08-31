#include <math.h>
#include <stdio.h>
#include "../inc/fourier.h"

#define PI 3.14159265
#define EPS .00001

void DFT(complex_t c[], int N, FILE* fp) {
	double re, im;

	for (int k = 0; k < N; k++) {
		re = im = 0;
		for (int n = 0; n < N; n++) {
			re += c[n].re * cos(-2 * PI * k * n / N) - c[n].im * sin(-2 * PI * k * n / N);
			im += c[n].re * sin(-2 * PI * k * n / N) + c[n].im * cos(-2 * PI * k * n / N);
		}
		re /= N;
		if (fabs(re) < EPS) {
			re = fabs(re);
		}
		im /= N;
		if (fabs(im) < EPS) {
			im = fabs(im);
		}
		fprintf(fp, "%3d:%8.4f,%8.4f,%8.4f\n", k, re, im, sqrt(pow(re, 2.0) + pow(im, 2.0)));
	}
}
