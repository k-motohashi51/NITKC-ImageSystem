/*
This program maked by j17407.
*/
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"
#define rand_range(min,max) (min)+(rand())%((max)-(min)+(1))
/*GYOUSYUKU*/
void Image_erosion4(int iw, int ih, imgdata* idata)
{
	for (int iy = 1; iy < ih - 1; iy++){
		for (int ix = 1; ix < iw - 1; ix++){
			unsigned char uc = idata->source[RED][iy + 0][ix + 0]; // 中央
			unsigned char ua = idata->source[RED][iy - 1][ix + 0]; // 上
			unsigned char ub = idata->source[RED][iy + 1][ix + 0]; // 下
			unsigned char ul = idata->source[RED][iy + 0][ix - 1]; // 左
			unsigned char ur = idata->source[RED][iy + 0][ix + 1]; // 右
			//
			unsigned char ux = 0xFF;
			if (uc != 0xFF) { ux = 0x00; }
			if (ua != 0xFF) { ux = 0x00; }
			if (ub != 0xFF) { ux = 0x00; }
			if (ul != 0xFF) { ux = 0x00; }
			if (ur != 0xFF) { ux = 0x00; }
			//
			idata->cwork[RED][iy][ix] = ux;
		}
	}
}
void Image_erosion8(int iw, int ih, imgdata* idata)
{
	for (int iy = 1; iy < ih - 1; iy++){
		for (int ix = 1; ix < iw - 1; ix++){
			unsigned char uc = idata->source[RED][iy + 0][ix + 0];
			unsigned char ua = idata->source[RED][iy - 1][ix + 0];
			unsigned char ub = idata->source[RED][iy + 1][ix + 0];
			unsigned char ul = idata->source[RED][iy + 0][ix - 1];
			unsigned char ur = idata->source[RED][iy + 0][ix + 1];
			unsigned char ual = idata->source[RED][iy - 1][ix - 1];
			unsigned char uar = idata->source[RED][iy - 1][ix + 1];
			unsigned char ubl = idata->source[RED][iy + 1][ix - 1];
			unsigned char ubr = idata->source[RED][iy + 1][ix + 1];
			//
			unsigned char ux = 0xFF;
			if (uc != 0xFF) { ux = 0x00; }
			if (ua != 0xFF) { ux = 0x00; }
			if (ub != 0xFF) { ux = 0x00; }
			if (ul != 0xFF) { ux = 0x00; }
			if (ur != 0xFF) { ux = 0x00; }
			if (ual != 0xFF) { ux = 0x00; }
			if (uar != 0xFF) { ux = 0x00; }
			if (ubl != 0xFF) { ux = 0x00; }
			if (ubr != 0xFF) { ux = 0x00; }
			//
			idata->cwork[RED][iy][ix] = ux;
		}
	}
}
/*BOUCYOU*/
void Image_dilation4(int iw, int ih, imgdata* idata)
{
	for (int iy = 1; iy < ih - 1; iy++){
		for (int ix = 1; ix < iw - 1; ix++){
			unsigned char uc = idata->source[RED][iy + 0][ix + 0];
			unsigned char ua = idata->source[RED][iy - 1][ix + 0];
			unsigned char ub = idata->source[RED][iy + 1][ix + 0];
			unsigned char ul = idata->source[RED][iy + 0][ix - 1];
			unsigned char ur = idata->source[RED][iy + 0][ix + 1];
			//
			unsigned char ux = 0x00;
			if (uc != 0x00) { ux = 0xFF; }
			if (ua != 0x00) { ux = 0xFF; }
			if (ub != 0x00) { ux = 0xFF; }
			if (ul != 0x00) { ux = 0xFF; }
			if (ur != 0x00) { ux = 0xFF; }
			//
			idata->cwork[RED][iy][ix] = ux;
		}
	}
}
void Image_dilation8(int iw, int ih, imgdata* idata)
{
	for (int iy = 1; iy < ih - 1; iy++){
		for (int ix = 1; ix < iw - 1; ix++){
			unsigned char uc = idata->source[RED][iy + 0][ix + 0];
			unsigned char ua = idata->source[RED][iy - 1][ix + 0];
			unsigned char ub = idata->source[RED][iy + 1][ix + 0];
			unsigned char ul = idata->source[RED][iy + 0][ix - 1];
			unsigned char ur = idata->source[RED][iy + 0][ix + 1];
			unsigned char ual = idata->source[RED][iy - 1][ix - 1];
			unsigned char uar = idata->source[RED][iy - 1][ix + 1];
			unsigned char ubl = idata->source[RED][iy + 1][ix - 1];
			unsigned char ubr = idata->source[RED][iy + 1][ix + 1];
			//
			unsigned char ux = 0x00;
			if (uc != 0x00) { ux = 0xFF; }
			if (ua != 0x00) { ux = 0xFF; }
			if (ub != 0x00) { ux = 0xFF; }
			if (ul != 0x00) { ux = 0xFF; }
			if (ur != 0x00) { ux = 0xFF; }
			if (ual != 0x00) { ux = 0xFF; }
			if (uar != 0x00) { ux = 0xFF; }
			if (ubl != 0x00) { ux = 0xFF; }
			if (ubr != 0x00) { ux = 0xFF; }
			//
			idata->cwork[RED][iy][ix] = ux;
		}
	}
}
void cp(imgdata* idata) {
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
	imgdata idata, _idata;
	double c;
	int x, y;
	// 例題プログラム
	// BMP ファイルをコピーするプログラム
	if (argc < 2) printf("使用法：cpbmp コピー元.bmp \n");
	else {
		if (readBMPfile(argv[1], &idata) > 0)
			printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		else {
			/* 例題：コピーするプログラム */
			for (y = 0; y < idata.height; y++)
				for (x = 0; x < idata.width; x++)
					idata.cwork[RED][y][x] = 128; //flag
			Image_erosion8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion8(idata.width, idata.height, &idata);
			cp(&idata);
			for (y = 0; y < idata.height; y++) {
				for (x = 0; x < idata.width; x++) {
					idata.results[RED][y][x] = idata.source[RED][y][x];
					idata.results[GREEN][y][x] = idata.source[RED][y][x];
					idata.results[BLUE][y][x] = idata.source[RED][y][x];
				}
			}
			if (writeBMPfile("ans19-3.bmp", &idata) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		}
		if (readBMPfile(argv[1], &idata) > 0)
			printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		else {
			Image_dilation8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion8(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation8(idata.width, idata.height, &idata);
			cp(&idata);
			for (y = 0; y < idata.height; y++) {
				for (x = 0; x < idata.width; x++) {
					idata.results[RED][y][x] = idata.source[RED][y][x];
					idata.results[GREEN][y][x] = idata.source[RED][y][x];
					idata.results[BLUE][y][x] = idata.source[RED][y][x];
				}
			}
			if (writeBMPfile("ans19-4.bmp", &idata) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		}
		if (readBMPfile(argv[1], &idata) > 0)
			printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		else {
			/* 例題：コピーするプログラム */
			Image_erosion4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion4(idata.width, idata.height, &idata);
			cp(&idata);
			for (y = 0; y < idata.height; y++) {
				for (x = 0; x < idata.width; x++) {
					idata.results[RED][y][x] = idata.source[RED][y][x];
					idata.results[GREEN][y][x] = idata.source[RED][y][x];
					idata.results[BLUE][y][x] = idata.source[RED][y][x];
				}
			}
			if (writeBMPfile("ans19-1.bmp", &idata) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		}
		if (readBMPfile(argv[1], &idata) > 0)
			printf("指定コピー元ファイル%s が見つかりません\n", argv[1]);
		else {
			/* 例題：コピーするプログラム */
			Image_dilation4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_erosion4(idata.width, idata.height, &idata);
			cp(&idata);
			Image_dilation4(idata.width, idata.height, &idata);
			cp(&idata);
			for (y = 0; y < idata.height; y++) {
				for (x = 0; x < idata.width; x++) {
					idata.results[RED][y][x] = idata.source[RED][y][x];
					idata.results[GREEN][y][x] = idata.source[RED][y][x];
					idata.results[BLUE][y][x] = idata.source[RED][y][x];
				}
			}
			if (writeBMPfile("ans19-2.bmp", &idata) > 0)
				printf("出力ファイル%s に保存できませんでした\n", argv[2]);
		}
	}
}
