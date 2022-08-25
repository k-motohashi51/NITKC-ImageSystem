#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "./inc/binarization.h"
#include "../inc/general.h"

// 固定閾値法
int fixed_threshold(imgdata* idata, int th) {
    int pivot_r, pivot_g, pivot_b;
    int color;

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
            pivot_r = idata->source[RED][y][x];
            pivot_g = idata->source[GREEN][y][x];
            pivot_b = idata->source[BLUE][y][x];

			if (th <= pivot_r && th <= pivot_g && th <= pivot_b) {
                color = WHITEVALUE;
			} else {
                color = BLACKVALUE;
			}
				idata->results[RED][y][x] = color;
				idata->results[GREEN][y][x] = color;
				idata->results[BLUE][y][x] = color;
		}
	}

	return E_SUCCESS;
}
