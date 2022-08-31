#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def550.h"
#include "var.h"
#include "bmpfile.h"

void matching(imgdata idata, imgdata template, int i, int j, double* rval, double* sval, double* dval) {
	double a = 0, b = 0, c = 0, d = 0;
	double add;
	int k, l;
	for (k = 0; k < template.height; k++) {
		for (l = 0; l < template.width; l++) {
			a += idata.source[RED][i + k][j + l] * template.source[RED][k][l];
			b += idata.source[RED][i + k][j + l] * idata.source[RED][i + k][j + l];
			c += template.source[RED][k][l] * template.source[RED][k][l];
			d += abs(idata.source[RED][i + k][j + l] - template.source[RED][k][l]);
		}
	}
	*rval = a / (sqrt(b) * sqrt(c));
	*sval = a;
	*dval = d;
}

int main(int argc, char* argv[])
{
	imgdata idata, template;
	double rm = -1, sm = -123456789, dm = 123456789, rval, sval, dval;
	int ri, rj, si, sj, di, dj, y, x;
	char outr[256];
	if (argc != 3) printf("使用法：%s 入力.bmp テンプレート.bmp\n", argv[0]);
	else {
		if (readBMPfile(argv[1], &idata) > 0 || readBMPfile(argv[2], &template))
			printf("指定入力ファイル%s が見つかりません\n", argv[1]);
		else {
			/* init idata */
			for (y = 0; y < idata.height; y++) {
				for (x = 0; x < idata.width; x++) {
					idata.results[RED][y][x] = idata.source[RED][y][x];
					if (idata.source[RED][y][x] == 255 &&
						idata.source[GREEN][y][x] == 255 && idata.source[BLUE][y][x] == 255)
						idata.source[RED][y][x] = 0;
					else
						idata.source[RED][y][x] = 1;
				}
			}
			/* init template */
			for (y = 0; y < template.height; y++) {
				for (x = 0; x < template.width; x++) {
					if (template.source[RED][y][x] == 255 &&
						template.source[GREEN][y][x] == 255 && template.source[BLUE][y][x] == 255)
						template.source[RED][y][x] = 0;
					else
						template.source[RED][y][x] = 1;
				}
			}
			/* calculate Correlation coefficient - Similar - Distance */
			for (y = 0; y < idata.height - template.height; y++) {
				for (x = 0; x < idata.width - template.width; x++) {
					matching(idata, template, y, x, &rval, &sval, &dval);
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
			/* Correlation coefficient */
			for (y = ri; y < ri + template.height; y++) {
				for (x = rj; x < rj + template.width; x++) {
					template.results[RED][y - ri][x - rj] = idata.results[RED][y][x];
					template.results[GREEN][y - ri][x - rj] = idata.results[RED][y][x];
					template.results[BLUE][y - ri][x - rj] = idata.results[RED][y][x];
				}
			}
			/* Answer of Correlation coefficient */
			sprintf(outr, "ans21-%cr.bmp", argv[2][5]);
			if (writeBMPfile(outr, &template) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
			/* Similar */
			for (y = si; y < si + template.height; y++) {
				for (x = sj; x < sj + template.width; x++) {
					template.results[RED][y - si][x - sj] = idata.results[RED][y][x];
					template.results[GREEN][y - si][x - sj] =
						idata.results[RED][y][x];
					template.results[BLUE][y - si][x - sj] = idata.results[RED][y][x];
				}
			}
			/* Answer of Similar */
			sprintf(outr, "ans21-%cs.bmp", argv[2][5]);
			if (writeBMPfile(outr, &template) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
			/* Distance */
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
		}
	}
}
