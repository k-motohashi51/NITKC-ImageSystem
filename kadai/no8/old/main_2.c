#include <stdio.h>
#include <stdlib.h>

#define MAX 256

void EnMonochrome(imgdata*);
void EqualizeHistgram(imgdata*);

int main(int argc, char* argv[])
{
    imgdata idata;
    double Y = 0;   // 輝度（モノクロ画像の濃淡値）

    if (argc < 3) {
        printf("usage：main src dst\n");
        exit(1);
    }

    if (readBMPfile(argv[1], &idata) > 0) {
        printf("src wasn't found.\n", argv[1]);
        exit(1);
    }

    EnMonochrome(&idata);
    EqualizeHistgram(&idata);

    // BMPファイルに保存
    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("couldn't save image into dst.");
    }

    return 0;
}

/* モノクロ化 */
void EnMonochrome(imgdata* idata)
{
    for (int i = 0; i < idata->height; i++) {
        for (int j = 0; j < idata->width; j++) {
            Y = 0.299 * idata->source[RED][j][i]
              + 0.587 * idata->source[GREEN][j][i]
              + 0.114 * idata->source[BLUE][j][i];
              
            idata->cwork[RED][j][i] = Y;
            idata->cwork[GREEN][j][i] = Y;
            idata->cwork[BLUE][j][i] = Y;
        }
    }
}

/* ヒストグラムの平均化 */
void EqualizeHistgram(imgdata* idata)
{
    int pixel_num;          // 全画素数
    int mean;               // 度数の平均値
    int hist[MAX] = {0};    // 濃度値kの画素数

    pixel_num = idata->height * idata->width;
    mean = pixel_num / pow(2, idata->color_depth);

    // ヒストグラムの作成
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            hist[idata->cwork[RED][x][y]]++;
        }
    }

    int sum = 0;
    for (int i = 0; i < MAX; i++) {
        sum += hist[i];
        printf("hist[%d] = %d\n", i, hist[i]);
    }
    printf("sum = %d\n", sum);
    
}
