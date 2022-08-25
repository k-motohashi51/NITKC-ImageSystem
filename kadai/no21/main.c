#include <stdio.h>
#include <stdlib.h>
#include "./inc/binarization.h"
#include "./inc/matching.h"

int main(int argc, char* argv[]) {
    imgdata idata;
    imgdata template;
    imgdata ans_r;

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

    if (fixed_threshold(&idata, WHITEVALUE) != E_SUCCESS) {
        printf("ERROR!\n");
        exit(1);
    }

    /* 処理 */
    match(&idata, &template, &ans_r);

    /* 出力 */
    if (writeBMPfile(argv[3], &ans_r) > 0) {
        printf("Can't save into %s.\n", argv[3]);
        exit(1);
    }

    return 0;
}
