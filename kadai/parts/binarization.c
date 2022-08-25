#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/binarization.h"
#include "../inc/general.h"

#define GLAY_MAX 256

// 固定閾値法
int fixed_threshold(imgdata* idata, int threshold) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (threshold <= idata->source[RED][y][x]) {
				idata->results[RED][y][x] = WHITEVALUE;
				idata->results[GREEN][y][x] = WHITEVALUE;
				idata->results[BLUE][y][x] = WHITEVALUE;
			} else {
				idata->results[RED][y][x] = BLACKVALUE;
				idata->results[GREEN][y][x] = BLACKVALUE;
				idata->results[BLUE][y][x] = BLACKVALUE;
			}
		}
	}

	return E_SUCCESS;
}

// モード法
int mode(imgdata* idata) {
	int hist[GLAY_MAX] = {0};
	int max_index;
	int max_index_2;
	int min_index;
	int threshold;

	histgram(idata, hist);

	max_index = 0;
	for (int i = 0; i < GLAY_MAX - 1; i++) {
		if (hist[max_index] <= hist[i + 1]) {
			max_index = i + 1;
		}
	}

	max_index_2 = max_index + 50;
	for (int i = max_index_2; i < GLAY_MAX - 1; i++) {
		if (hist[max_index_2] < hist[i + 1]) {
			max_index_2 = i + 1;
		}
	}
	
	min_index = max_index;
	for (int i = max_index; i < max_index_2; i++) {
		if (hist[min_index] > hist[i + 1]) {
			min_index = i + 1;
		}
	}

	threshold = min_index;

	return threshold;
}

// 可変閾値法
int variable_threshold(imgdata* idata, int vb) {
	int n;			// 局所領域マスの合計数
	int na;			// 局所領域マスの合計数（端のとき含む）
	int range;		// 局所領域の一辺
	int** local;	// 局所領域の各々のマスの濃度値を格納
	int* lb;		// 局所領域配列のメモリ確保用
	int	offset;		// 局所領域走査時のオフセット
	int m;			// 局所領域の平均値
	int v;			// 局所領域の分散
	int th;			// 閾値
	int gray;		// 濃度値
	int pre_gray;	// 濃度値

	range = 7;
	n = (int)pow(range, 2.0);
	offset = -(range / 2);;		
	pre_gray = 0;

	// 局所領域用二次元配列のメモリ確保
	local = malloc(sizeof(int*) * range);
	lb = malloc(sizeof(int) * range * range);
	for (int i = 0; i < range; i++) {
		local[i] = lb + i * range;
	}

	for (int y = 0; y < idata->height; y++) {
		th = 0;	// 左端での閾値は定まらないので0とする
		for (int x = 0; x < idata->width; x++) {
			na = n;
			// 局所領域の値を二次元配列に格納
			for (int j = 0; j < range; j++) {
				for (int i = 0; i < range; i++) {
					// 範囲内か否かの判断
					if (((0 <= y + j + offset) && (y + j + offset < idata->height))
						&& ((0 <= x + i + offset) && (x + i + offset < idata->width))) {
						local[j][i] = idata->source[RED][y + j + offset][x + i + offset];
					} else {
						na--;
						local[j][i] = 0;
					}
				}
			}
			// 更新の判断
			m = mean(na, local, range);
			v = variance(na, local, m, range);

			if (vb <= v) {
				// 反転する

				th = m;	// 平均値を2値化の閾値とする

				if (idata->source[RED][y][x] < th) {
					gray = WHITEVALUE;
				} else {
					gray = BLACKVALUE;
				}

				idata->source[RED][y][x] = gray;
				idata->source[GREEN][y][x] = gray;
				idata->source[BLUE][y][x] = gray;
				pre_gray = gray;
			} else {
				// 前の処理結果と同じ
				idata->results[RED][y][x] = pre_gray;
				idata->results[GREEN][y][x] = pre_gray;
				idata->results[BLUE][y][x] = pre_gray;
			}
		}
	}


	free(lb);
	free(local);

	return E_SUCCESS;
}

void expand(imgdata* idata, int neighbor) {
    
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            if (idata->cwork[RED][y][x] == BLACKVALUE) {
                // 近傍領域を黒にする
                for (int j = -1; j < 1; j++) {
                    for (int i = -1; i < 1; i++) {
                        // 4近傍時は角を除外
                        if (neighbor == 4 && abs(i) == 1 && abs(j) == 1) {
                            continue;
                        }

                        // 範囲外
                        if (y + j < 0 || idata->height <= y + j) {
                            continue;
                        }
                        if (x + i < 0 || idata->width <= x + i) {
                            continue;
                        }

                        idata->work[RED][y + j][x + i] = BLACKVALUE;
                        idata->work[GREEN][y + j][x + i] = BLACKVALUE;
                        idata->work[BLUE][y + j][x + i] = BLACKVALUE;
                    }
                }
            } else {
                idata->work[RED][y][x] = WHITEVALUE;
                idata->work[GREEN][y][x] = WHITEVALUE;
                idata->work[BLUE][y][x] = WHITEVALUE;
            }
        }
    }

    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            idata->cwork[RED][y][x] = idata->work[RED][y][x];
            idata->cwork[GREEN][y][x] = idata->work[GREEN][y][x];
            idata->cwork[BLUE][y][x] = idata->work[BLUE][y][x];
        }
    }
}

void contract(imgdata* idata, int neighbor) {
    int flag = 0;

    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {

            if (idata->cwork[RED][y][x] == BLACKVALUE) {
                flag = 0;
                for (int j = -1; j < 1; j++) {
                    for (int i = -1; i < 1; i++) {
                        // 4近傍時は角を除外
                        if (neighbor == 4 && abs(i) == 1 && abs(j) == 1) {
                            continue;
                        }

                        // 範囲外
                        if (y + j < 0 || idata->height <= y + j) {
                            continue;
                        }
                        if (x + i < 0 || idata->width <= x + i) {
                            continue;
                        }

                        // 一つでも周りに白があったら自身も白に
                        if (idata->cwork[RED][y + j][x + i] == WHITEVALUE) {
                            flag = 1;
                            break;
                        }
                    }

                    if (flag == 1) {
                        break;
                    }
                }
                
                idata->work[RED][y][x] = (flag == 1) ? WHITEVALUE : BLACKVALUE;

            } else {
                idata->work[RED][y][x] = WHITEVALUE;
                idata->work[GREEN][y][x] = WHITEVALUE;
                idata->work[BLUE][y][x] = WHITEVALUE;
            }
        }
    }

    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            idata->cwork[RED][y][x] = idata->work[RED][y][x];
            idata->cwork[GREEN][y][x] = idata->work[GREEN][y][x];
            idata->cwork[BLUE][y][x] = idata->work[BLUE][y][x];
        }
    }
}
