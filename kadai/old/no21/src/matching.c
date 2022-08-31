#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/matching.h"

void matching(imgdata F, imgdata T, int i, int j, double* rval, double* sval, double* dval) {
	//double pcor, psim, pdist;	// 注目画素の結果
	//double cor, sim, dist;	// 最高の結果
	double a = 0, b = 0, c = 0, d = 0;

	for (int k = 0; k < T.height; k++) {
		for (int l = 0; l < T.width; l++) {
			printf("in matching\n");
			a += F.source[RED][i + k][j + l] * T.source[RED][k][l];
			b += F.source[RED][j + l][i + k] * F.source[RED][i + k][j + l];
			c += T.source[RED][k][l] * T.source[RED][k][l];
			d += abs(F.source[RED][i + k][j + l] - T.source[RED][k][l]);
		}
	}
	*rval = a / (sqrt(b) * sqrt(c));
	*sval = a;
	*dval = d;
}
