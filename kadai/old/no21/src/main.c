#include <stdio.h>
#include <stdlib.h>
#include "../inc/bmpfile.h"
#include "../inc/var.h"
#include "../inc/def550.h"
#include "../inc/matching.h"

int main(int argc, char* argv[]) {
    imgdata idata;
    imgdata template;
		double rm = -1, sm = -123456789, dm = 123456789;
		double rval, sval, dval;
		int ri, rj , si , sj ,  di , dj ,  y , x ;
		char outr[256];

    /* 入力 */
    if (argc < 3) {
        printf("usage：main in21.bmp in21-*t.bmp ans21-**.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("[%s] wasn't found\n", argv[1]);
        exit(1);
    }

    if (readBMPfile(argv[2], &template) > 0) {
        printf("[%s] wasn't found\n", argv[2]);
        exit(1);
    }

		// image dataの初期化
		for (int y = 0; y < idata.height; y++) {
			for (int x = 0; x < idata.width; x++) {
				idata.results[RED][y][x] = idata.source[RED][y][x];
				if (idata.source[RED][y][x] == 255 &&
					idata.source[GREEN][y][x] == 255 &&
					idata.source[BLUE][y][x] == 255) {
					idata.source[RED][y][x] = 0;
				} else {
					idata.source[RED][y][x] = 1;
				}
			}
		}

		// テンプレートの初期化
		for (int y = 0; y < template.height; y++) {
			for (int x = 0; x < template.width; x++) {
				template.results[RED][y][x] = template.source[RED][y][x];
				if (template.source[RED][y][x] == 255 &&
					template.source[GREEN][y][x] == 255 &&
					template.source[BLUE][y][x] == 255) {
					template.source[RED][y][x] = 0;
				} else {
					idata.source[RED][y][x] = 1;
				}
			}
		}

		for (int y = 0; y < idata.height - template.height; y++) {
			for (int x = 0; x < idata.width - template.width; x++) {
				matching(idata, template, x, y, &rval, &sval, &dval);
				if (rm < rval) {
					ri = y;
					rj = x;
					rm = rval;
				}
				if (sm <= sval) {
					si = y;
					sj = x;
					sm = sval;
				}
				if (dm >= dval) {
					di = y;
					dj = x;
					dm = dval;
				}
			}
		}

		for (y = ri; y < ri + template.height; y++) {
			for (x = rj; x < rj + template.width; x++) {
				template.results[RED][y - ri][x - rj] = idata.results[RED][y][x];
				template.results[GREEN][y - ri][x - rj] = idata.results[RED][y][x];
				template.results[BLUE][y - ri][x - rj] = idata.results[RED][y][x];
			}
		}

		/* 相関係数 */
		sprintf(outr, "ans21-%cr.bmp", argv[2][5]);
		if (writeBMPfile(outr, &template) > 0)
			printf("出力ファイル%s に保存できませんでした\n", argv[2]);

		/* 類似度 */
		for (y = si; y < si + template.height; y++) {
			for (x = sj; x < sj + template.width; x++) {
				template.results[RED][y - si][x - sj] = idata.results[RED][y][x];
				template.results[GREEN][y - si][x - sj] =
					idata.results[RED][y][x];
				template.results[BLUE][y - si][x - sj] = idata.results[RED][y][x];
			}
		}
		sprintf(outr, "ans21-%cs.bmp", argv[2][5]);
		if (writeBMPfile(outr, &template) > 0)
			printf("出力ファイル%s に保存できませんでした\n", argv[2]);

		/* 距離 */
		for (y = di; y < di + template.height; y++) {
			for (x = dj; x < dj + template.width; x++) {
				template.results[RED][y - di][x - dj] = idata.results[RED][y][x];
				template.results[GREEN][y - di][x - dj] =
					idata.results[RED][y][x];
				template.results[BLUE][y - di][x - dj] = idata.results[RED][y][x];
			}
		}
		/* Answer of Distance */
		sprintf(outr, "ans21-%cd.bmp", argv[2][5]);
		if (writeBMPfile(outr, &template) > 0)
			printf("出力ファイル%s に保存できませんでした\n", argv[2]);

		return 0;
}
