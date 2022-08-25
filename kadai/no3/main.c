#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define E_SUCCESS 0

int flip_horizontally(imgdata*);

int main(int argc, char* argv[]) {
    imgdata idata;

    if (argc < 3) {
        printf("usage：main in8.bmp ans8.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("in file wasn't found\n", argv[1]);
        exit(1);
    }

    if (flip_horizontally(&idata) != E_SUCCESS) {
        printf("ERROR!\n");
        exit(1);
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
        exit(1);
    }

    return 0;
}

int flip_horizontally(imgdata* idata) {
    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width / 2; x++) {
            // 左半分を保存
            idata->cwork[RED][y][x] = idata->source[RED][y][x];
            idata->cwork[GREEN][y][x] = idata->source[GREEN][y][x];
            idata->cwork[BLUE][y][x] = idata->source[BLUE][y][x];
            // 右半分を左半分へ移動
            idata->results[RED][y][x] = idata->source[RED][y][idata->width - x - 1];
            idata->results[GREEN][y][x] = idata->source[GREEN][y][idata->width - x - 1];
            idata->results[BLUE][y][x] = idata->source[BLUE][y][idata->width - x - 1];
            // 保存した左半分を右半分へ
            idata->results[RED][y][idata->width - x - 1] = idata->cwork[RED][y][x];
            idata->results[GREEN][y][idata->width - x - 1] = idata->cwork[GREEN][y][x];
            idata->results[BLUE][y][idata->width - x - 1] = idata->cwork[BLUE][y][x];
        }
    }

    return E_SUCCESS;
}
