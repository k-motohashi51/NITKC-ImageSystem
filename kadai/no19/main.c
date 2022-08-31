#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"


void contract4(imgdata* idata) {
	unsigned char c, w, s, a, d;
	char color;

	for (int j = 1; j < idata->height - 1; j++) {
		for (int i = 1; i < idata->width - 1; i++) {
			c = idata->source[RED][j + 0][i + 0]; // 中央
			w = idata->source[RED][j - 1][i + 0]; // 上
			s = idata->source[RED][j + 1][i + 0]; // 下
			a = idata->source[RED][j + 0][i - 1]; // 左
			d = idata->source[RED][j + 0][i + 1]; // 右

			color = WHITEVALUE;
			if (c != WHITEVALUE) color = BLACKVALUE;
			if (w != WHITEVALUE) color = BLACKVALUE;
			if (s != WHITEVALUE) color = BLACKVALUE;
			if (a != WHITEVALUE) color = BLACKVALUE;
			if (d != WHITEVALUE) color = BLACKVALUE;

			idata->cwork[RED][j][i] = color;
		}
	}
}

void contract8(imgdata* idata) {
	unsigned char c, w, s, a, d, wa, wd, sa, sd;
	char color;

	for (int j = 1; j < idata->height - 1; j++){
		for (int i = 1; i < idata->width - 1; i++){
			c  = idata->source[RED][j + 0][i + 0];
			w  = idata->source[RED][j - 1][i + 0];
			s  = idata->source[RED][j + 1][i + 0];
			a  = idata->source[RED][j + 0][i - 1];
			d  = idata->source[RED][j + 0][i + 1];
			wa = idata->source[RED][j - 1][i - 1];
			wd = idata->source[RED][j - 1][i + 1];
			sa = idata->source[RED][j + 1][i - 1];
			sd = idata->source[RED][j + 1][i + 1];

			color = WHITEVALUE;
			if (c  != WHITEVALUE) color = BLACKVALUE;
			if (w  != WHITEVALUE) color = BLACKVALUE;
			if (s  != WHITEVALUE) color = BLACKVALUE;
			if (a  != WHITEVALUE) color = BLACKVALUE;
			if (d  != WHITEVALUE) color = BLACKVALUE;
			if (wa != WHITEVALUE) color = BLACKVALUE;
			if (wd != WHITEVALUE) color = BLACKVALUE;
			if (sa != WHITEVALUE) color = BLACKVALUE;
			if (sd != WHITEVALUE) color = BLACKVALUE;

			idata->cwork[RED][j][i] = color;
		}
	}
}

void expand4(imgdata* idata) {
	unsigned char c, w, s, a, d;
	char color;
	for (int j = 1; j < idata->height - 1; j++){
		for (int i = 1; i < idata->width - 1; i++){
			c = idata->source[RED][j + 0][i + 0];
			w = idata->source[RED][j - 1][i + 0];
			s = idata->source[RED][j + 1][i + 0];
			a = idata->source[RED][j + 0][i - 1];
			d = idata->source[RED][j + 0][i + 1];

			color = BLACKVALUE;
			if (c != BLACKVALUE) color = WHITEVALUE;
			if (w != BLACKVALUE) color = WHITEVALUE;
			if (s != BLACKVALUE) color = WHITEVALUE;
			if (a != BLACKVALUE) color = WHITEVALUE;
			if (d != BLACKVALUE) color = WHITEVALUE;

			idata->cwork[RED][j][i] = color;
		}
	}
}

void expand8(imgdata* idata) {
	unsigned char c, w, s, a, d, wa, wd, sa, sd;
	char color;

	for (int j = 1; j < idata->height - 1; j++){
		for (int i = 1; i < idata->width - 1; i++){
			c  = idata->source[RED][j + 0][i + 0];
			w  = idata->source[RED][j - 1][i + 0];
			s  = idata->source[RED][j + 1][i + 0];
			a  = idata->source[RED][j + 0][i - 1];
			d  = idata->source[RED][j + 0][i + 1];
			wa = idata->source[RED][j - 1][i - 1];
			wd = idata->source[RED][j - 1][i + 1];
			sa = idata->source[RED][j + 1][i - 1];
			sd = idata->source[RED][j + 1][i + 1];

			color = BLACKVALUE;
			if (c  != BLACKVALUE) color = WHITEVALUE;
			if (w  != BLACKVALUE) color = WHITEVALUE;
			if (s  != BLACKVALUE) color = WHITEVALUE;
			if (a  != BLACKVALUE) color = WHITEVALUE;
			if (d  != BLACKVALUE) color = WHITEVALUE;
			if (wa != BLACKVALUE) color = WHITEVALUE;
			if (wd != BLACKVALUE) color = WHITEVALUE;
			if (sa != BLACKVALUE) color = WHITEVALUE;
			if (sd != BLACKVALUE) color = WHITEVALUE;

			idata->cwork[RED][j][i] = color;
		}
	}
}

void copy(imgdata* idata) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			if (idata->cwork[RED][y][x] != 128)
				idata->source[RED][y][x] = idata->cwork[RED][y][x];
			else
				idata->source[RED][y][x] = 255;
			idata->cwork[RED][y][x] = 128;
		}
	}
}

int main(int argc, char* argv[])
{
	imgdata idata;

	if (argc < 2) {
		printf("使用法：cpbmp コピー元.bmp \n");
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		exit(1);
	}

	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			idata.cwork[RED][y][x] = 128; //flag
		}
	}

	contract8(&idata);
	copy(&idata);
	expand8(&idata);
	copy(&idata);
	expand8(&idata);
	copy(&idata);
	contract8(&idata);
	copy(&idata);

	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			idata.results[RED][y][x] = idata.source[RED][y][x];
			idata.results[GREEN][y][x] = idata.source[RED][y][x];
			idata.results[BLUE][y][x] = idata.source[RED][y][x];
		}
	}

	if (writeBMPfile("ans19-3.bmp", &idata) > 0) {

		printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		exit(1);
	}

	expand8(&idata);
	copy(&idata);
	contract8(&idata);
	copy(&idata);
	contract8(&idata);
	copy(&idata);
	expand8(&idata);
	copy(&idata);

	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			idata.results[RED][y][x] = idata.source[RED][y][x];
			idata.results[GREEN][y][x] = idata.source[RED][y][x];
			idata.results[BLUE][y][x] = idata.source[RED][y][x];
		}
	}

	if (writeBMPfile("ans19-4.bmp", &idata) > 0) {exit(1);	
		printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		exit(1);	
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		exit(1);
	}

	contract4(&idata);
	copy(&idata);
	expand4(&idata);
	copy(&idata);
	expand4(&idata);
	copy(&idata);
	contract4(&idata);
	copy(&idata);

	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			idata.results[RED][y][x] = idata.source[RED][y][x];
			idata.results[GREEN][y][x] = idata.source[RED][y][x];
			idata.results[BLUE][y][x] = idata.source[RED][y][x];
		}
	}

	if (writeBMPfile("ans19-1.bmp", &idata) > 0) {
		printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		exit(1);
	}

	expand4(&idata);
	copy(&idata);
	contract4(&idata);
	copy(&idata);
	contract4(&idata);
	copy(&idata);
	expand4(&idata);
	copy(&idata);

	for (int y = 0; y < idata.height; y++) {
		for (int x = 0; x < idata.width; x++) {
			idata.results[RED][y][x] = idata.source[RED][y][x];
			idata.results[GREEN][y][x] = idata.source[RED][y][x];
			idata.results[BLUE][y][x] = idata.source[RED][y][x];
		}
	}
	if (writeBMPfile("ans19-2.bmp", &idata) > 0) {
		printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		exit(1);
	}
}
