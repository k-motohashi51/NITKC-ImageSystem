#include <stdlib.h>
#include "../inc/noise_removal.h"
#include "../inc/def.h"

void expand(imgdata* idata, int neighbor_num) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (idata->cwork[RED][y][x] == BLACKVALUE) {
				// 近傍を黒く塗る
				for (int j = -1; j < 1; j++) {
					// yの範囲外
					if ((y + j < 0) || (idata->height <= y + j)) {
						continue;
					}
					for (int i = -1; i < 1; i++) {
						// xの範囲外
						if ((x + i < 0) || (idata->width <= x + i)) {
							continue;
						}

						// 4近傍のとき、角は含めない
						if (neighbor_num == 4) {
							if (abs(i) == 1 && abs(j) == 1) {
								continue;
							}
						}

						idata->work[RED][y + j][x + i] = BLACKVALUE;
					}
				}
			} else {
				idata->work[RED][y][x] = idata->cwork[RED][y][x];
			}
		}
	}

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			idata->cwork[RED][y][x] = idata->work[RED][y][x];
			idata->cwork[GREEN][y][x] = idata->work[RED][y][x];
			idata->cwork[BLUE][y][x] = idata->work[RED][y][x];
		}
	}
}

void contract(imgdata* idata, int neighbor_num) {
	int white_exist;

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (idata->cwork[RED][y][x] == BLACKVALUE) {
				white_exist = 0;
				for (int j = -1; j < 1; j++) {
					for (int i = -1; i < 1; i++) {
						// 範囲外
						if ((x + i < 0) || (idata->width <= x + i)) {
							continue;
						}
						if ((y + j < 0) || (idata->height <= y + j)) {
							continue;
						}

						// 4近傍のとき、角は含めない
						if (neighbor_num == 4) {
							if (abs(i) == 1 && abs(i) == 1) {
								continue;
							}
						}

						// 白発見
						if (idata->cwork[RED][y + j][x + i] == WHITEVALUE) {
							white_exist = 1;
							break;
						}
					}
					if (white_exist == 1) {
						break;
					}
				}

				idata->work[RED][y][x] = (white_exist == 1) ? WHITEVALUE : BLACKVALUE;
			} else {
				idata->work[RED][y][x] = idata->cwork[RED][y][x];
			}
		}
	}

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			idata->cwork[RED][y][x] = idata->work[RED][y][x];
			idata->cwork[GREEN][y][x] = idata->work[RED][y][x];
			idata->cwork[BLUE][y][x] = idata->work[RED][y][x];
		}
	}
}
