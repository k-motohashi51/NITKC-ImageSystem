#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define H_NUM 256

void EqualizeHistgram(imgdata*);

int main(int argc, char* argv[])
{
    imgdata idata;
    
    if (argc < 3) {
        printf("usage：main in8.bmp ans8.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("in file wasn't found\n", argv[1]);
        exit(1);
    }

    EqualizeHistgram(&idata);

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
    }

    return 0;
}

void EqualizeHistgram(imgdata* idata)
{
    int h[H_NUM] = {0};
    int pixel_num = idata->height * idata->width;
    int depth = pow(2, idata->color_depth);
    int m = pixel_num / depth;
    int nm[H_NUM][H_NUM] = {0};
    int want = 0;
    int ex = 0;
    int cnt[H_NUM][H_NUM] = {0};

    printf("全画素数 = %d\n", pixel_num);
    printf("bit階調 = %d\n", idata->color_depth);
    printf("階調数 = %d\n", depth);
    printf("度数の平均値 = %d\n", m);

    // ヒストグラムの作成
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            h[idata->source[RED][y][x]]++;
        }
    }

    // 移動する画素値を決定
    for (int i = 0; i < H_NUM; i++) {
        if (h[i] < m) {
            want = m - h[i];

            // 隣からもらう
            for (int j = i + 1; j < H_NUM; j++) {
                if (want <= h[j]) { // まかなえる
                    nm[j][i] = h[j] - want;
                    h[j] -= want;
                    break;
                } else {    // まだ足りない
                    nm[j][i] += h[j];
                    want -= h[j];
                    h[j] = 0;
                }
            }
            continue;


        }

        if (m < h[i]) {
            nm[i][i + 1] = h[i] - m; // 隣にあげる
        }
    }

    // 平均化
    int current;
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            current = idata->source[RED][y][x];
            for (int k = 0; k < H_NUM; k++) {
                if (cnt[current][k] < nm[current][k]) {
                    idata->results[RED][y][x] = k;
                    idata->results[GREEN][y][x] = k;
                    idata->results[BLUE][y][x] = k;

                    cnt[current][k]++;
                }
            }
        }

    }
}
