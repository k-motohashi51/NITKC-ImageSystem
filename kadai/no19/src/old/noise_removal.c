#include <stdlib.h>
#include "../inc/noise_removal.h"
#include "../inc/def.h"

int is_out(int i, int j) {
	if (i < 0 || 255 < i || j < 0 || 255 < j) {
		return 1;
	} else {
		return 0;
	}
}

void expand(imgdata* idata, int next_num) {
	int black_cnt;

	for (int y = 0; y < idata->height; y ++) {
		for (int x = 0; x < idata->width; x ++) {
			// 近傍に一つでも黒があれば注目画素を黒に変える
			if (idata->cwork[RED][y][x] == WHITEVALUE) {
				black_cnt = 0;
				// 近傍を走査する
				for (int j = y - 1; j < y + 1; j ++) {
					for (int i = x - 1; i < x + 1; i ++) {
						// 4近傍のときは角を考慮しない 
						if (next_num == 4) {
							if (abs(i) == 1 && abs(j) == 1) {
								continue;
							}
						}
						// 近傍が範囲外
						if (is_out(i, j) == 1) {
							continue;
						}

						// 近傍が黒であった
						if (idata->cwork[RED][j][i] == BLACKVALUE) {
							black_cnt ++;
						}
					}
				}
				// 1つでも黒があれば
				idata->work[RED][y][x] = (black_cnt > 0) ? BLACKVALUE : WHITEVALUE;
			} else {
				// 現状維持
				idata->work[RED][y][x] = idata->cwork[RED][y][x];
			}
		}
	}

	// cworkを変更後の状態とする
	for (int y = 0; y < idata->height; y ++) {
		for (int x = 0; x < idata->width; x ++) {
			idata->cwork[RED][y][x] = idata->work[RED][y][x];
			idata->cwork[GREEN][y][x] = idata->work[RED][y][x];
			idata->cwork[BLUE][y][x] = idata->work[RED][y][x];
		}
	}
}

void contract(imgdata* idata, int next_num) {
	int white_cnt;

	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (idata->cwork[RED][y][x] == BLACKVALUE) {
				white_cnt = 0;
				// 近傍を走査する
				for (int j = y - 1; j < y + 1; j++) {
					for (int i = x - 1; i < x + 1; i++) {
						// 範囲外
						if (is_out(i, j) == 1){
							white_cnt++;
							continue;
						}
						// 4近傍のとき、角の処理を除外
						if (next_num == 4) {
							if (abs(i) == 1 && abs(j) == 1) {
								continue;
							}
						}

						// 白がある
						if (idata->cwork[RED][j][i] == WHITEVALUE) {
							white_cnt ++;
						}
					}
				}
				idata->work[RED][y][x] = (white_cnt > 1) ? WHITEVALUE : BLACKVALUE;
			} else {
				// 現状維持
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
