#include "histgram.h"
#include <stdio.h>

int histgram(imgdata* idata, int* hist) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			hist[idata->source[RED][y][x]]++;
		}
	}

	return E_SUCCESS;
}
