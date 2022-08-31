#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bmpfile.h"
#include "def.h"
#include "var.h"
#define NUM 256

int main(int argc, char* argv[])
{
	imgdata idata;
	int h[NUM];
	int dp[NUM];
	int nm[NUM][NUM];
	int count[NUM][NUM];
	int m, n, d, k, g;
	int temp;
	int sum;
	int depth; 


	if (argc < 3) {
		printf("使用法：%s 入力.bmp 出力.bmp\n", argv[0]);
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("指定入力ファイル%sが見つかりません\n", argv[1]);
		exit(1);
	}

	// ヒストグラム作成
	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			temp = idata.source[RED][y][x];
			nm[temp][temp]++;
			h[temp]++;
			dp[temp] = 1;
		}
	}

	for (int x = 0; x < NUM; x++) {
		depth = (dp[x] == 1) ? depth + 1 : depth;
		sum += h[x];
	}

	m = pow(NUM, 2.0) / NUM;

	for (int x = 0; x < NUM; x++) {
		n = 0;

		for (int k = 0; k < NUM; k++) {
			n += nm[k][x];
		}

		if (n < m) {
			for (int y = 1; (y < NUM && n < m); y++) {
				if (nm[x + y][x + y] != 0) {
					if (n + nm[x + y][x + y] <= m) {
						nm[x + y][x] = nm[x + y][x + y];
						n += nm[x + y][x + y];
						nm[x + y][x + y] = 0;
					} else if (n + nm[x + y][x + y] > m) {
						d = m - n;
						nm[x + y][x] = d;
						n += d;
						nm[x + y][x + y] -= d;
					}
				}
			}
		} else if (m < n) {
			for (int y = NUM - 1; y >= 0 && n > m; y--) {
				if (nm[y][x] != 0) {
					if (n - nm[y][x] > m) {
						nm[y][x + 1] = nm[y][x];
						n -= nm[y][x];
						nm[y][x] = 0;
					} else if (n - nm[y][x] <= m) {
						d = n - m;
						nm[y][x + 1] = d;
						n -= d;
						nm[y][x] -= d;
					}
				}
			}
		}
	}

	for (int y = idata.height - 1; y >= 0; y--) {
		for (int x = 0; x < idata.width; x++) {
			g = idata.source[RED][y][x];
			for (int k = 0; k < NUM; k++) {
				if (count[g][k] < nm[g][k]) {
					idata.results[RED][y][x] = idata.results[GREEN][y][x] = idata.results[BLUE][y][x] = k;
					count[g][k]++;
					break;
				}
			}
			if (k == NUM)
				idata.results[RED][y][x] = idata.results[GREEN][y][x] = idata.results[BLUE][y][x] = g;
		}
	}

	if (writeBMPfile(argv[2], &idata) > 0) {
		printf("出力ファイル%sに保存できませんでした\n", argv[2]);
	}

	return 0;
}
