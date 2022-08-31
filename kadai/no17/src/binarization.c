#include "../inc/binarization.h"
#include <stdlib.h>
#include <math.h>
#include "../inc/def.h"

void variable_threshold(imgdata* idata) {
	int change;
	int sum;
	int num;
	int average;
	int pre = 0;
	int sigma;

	for (int y = 0; y < idata->height; y++) {
		pre = 0;
		change = 0;
		for (int x = 0; x < idata->width; x++) {
			sum = 0;
			num = 0;
			average = 0;
			sigma = 0;
			for (int j = y - 3; j <= y + 3; j++) {
				for (int i = x - 3; i <= x + 3; i++) {
					// 範囲外
					if (i < 0 || 255 < i) {
						continue;
					}
					if (j < 0 || 255 < j) {
						continue;
					}

					sum += idata->source[RED][j][i];
					num ++;
				}
			}
			average = sum / num;

			for (int j = y - 3; j <= y + 3; j++) {
				for (int i = x - 3; i <= x + 3; i++) {
					// 範囲外
					if (i < 0 || idata->width <= i) {
						continue;
					}
					if (j < 0 || idata->height <= j) {
						continue;
					}

					sigma += (idata->source[RED][j][i]-average)*(idata->source[RED][j][i]-average);
				}
			}

			if ((sigma / (num * 1.0)) >= 1000) {
				pre = average;
			}
			if (idata->source[RED][y][x] >= pre) {
				change = WHITEVALUE;
			} else {
				change = BLACKVALUE;
			}

			idata->results[RED][y][x] = change;
			idata->results[GREEN][y][x] = change;
			idata->results[BLUE][y][x] = change;
		}
	}
}
