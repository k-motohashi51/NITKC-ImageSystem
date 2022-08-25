#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define MAX 256

void EqualizeHistgram(imgdata*);

int main(int argc, char* argv[])
{
    imgdata idata;
    double Y = 0;   // 輝度Y(モノクロ画像の濃淡値)

    if (argc < 3) {
        printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
        exit(1);
    }

    for (int i = 0; i < idata.height; i++) {
        for (int j = 0; j < idata.width; j++) {
            Y = 0.299 * idata.source[RED][j][i] 
                + 0.587 * idata.source[GREEN][j][i] 
                + 0.114 * idata.source[BLUE][j][i];

            idata.cwork[RED][j][i] = Y;
            idata.cwork[GREEN][j][i] = Y;
            idata.cwork[BLUE][j][i] = Y;
        }
    }

    EqualizeHistgram(&idata);

    // BMPファイルに保存
    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("コピー先ファイル%sに保存できませんでした\n",argv[1]);
    }

    return 0; 
}


/* ヒストグラムの平均化 */
void EqualizeHistgram(imgdata* idata)
{
    int pixel_num = 0;  // 全画素数
    int hist[MAX] = {0};             // 各濃度値の個数
    int mean = 0;   // 度数の平均値
    int dist;
    int nmove[MAX][MAX] = {0};
    int cnt[MAX][MAX] = {0};
    int g;  // 注目画素の濃度値

    pixel_num = idata->height * idata->width;
    mean = pixel_num / pow(2, idata->color_depth);

    /* ヒストグラムの計算 */
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            hist[idata->cwork[RED][x][y]] ++;
        }
    }

    // デバッグ: ヒストグラムOK---------
    /*int sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += hist[i];
        printf("hist[%d] = %d\n", i, hist[i]);
    }
    printf("sum = %d\n", sum);*/
    //----------------------------------

    printf("mean = %d\n", mean);
    printf("color_depth = %d\n", idata->color_depth);

    /* 各濃度の移動画素数を決定 */
    for (int k = 0; k < MAX; k++) {
        /* 平均より小さい */
        if (hist[k] < mean) {
            nmove[k + 1][k] = mean - hist[k];   // 不足分の濃度値数
            /* となりから不足分の濃度値数を補う */
            for (int i = 1; hist[k] != mean; i++) {
                if (nmove[k + i][k] <= hist[k + i]) {   // となりの分だけでまかなえる
                    hist[k] = mean;
                    hist[k + i] -= nmove[k + i][k];    
                    break;
                } else {    // 隣の分だけでは足りない
                    nmove[k + i + 1][k] = nmove[k + i][k] - hist[k + i];  // 足りない分
                    hist[k] += hist[k + i];
                    hist[k + i] = 0;
                }
            }

        }

        /* 平均より大きい */
        if (mean < hist[k]) {
            nmove[k][k + 1] = hist[k] - mean;
            hist[k + 1] += nmove[k][k + 1];
            hist[k] = mean;
        }
    }

    /* nmoveをもとに、画素値を変更 */
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            g = idata->cwork[RED][y][x];    // 注目画素
            /* 注目画素の濃度値が移動対象となる、濃度値kを探す */
            for (int k = 0; k < MAX; k++) {
                if (cnt[g][k] < nmove[g][k]) {
                    cnt[g][k] ++;
                    idata->cwork[RED][y][x] = k;
                } else {
                    break;
                }
            }
        }
    }
}
