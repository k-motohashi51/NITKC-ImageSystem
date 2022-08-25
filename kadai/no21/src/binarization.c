#include "../inc/binarization.h"
#include "../inc/def550.h"

// 固定閾値法
void fixed_threshold(imgdata* idata, int th) {
    int r, g, b;
    int color;

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
            r = idata->source[RED][y][x];
            g = idata->source[GREEN][y][x];
            b = idata->source[BLUE][y][x];

			if (th == r && th == g && th == b) {
                color = WHITEVALUE;
			} else {
                color = BLACKVALUE;
			}

			idata->cwork[RED][y][x] = color;
			idata->cwork[GREEN][y][x] = color;
			idata->cwork[BLUE][y][x] = color;
		}
	}
}
