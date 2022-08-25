#include <stdio.h>
#include <stdlib.h>
#include "../inc/bmpfile.h"
#include "../inc/var.h"
#include "../inc/def550.h"
#include "../inc/binarization.h"
#include "../inc/matching.h"

int main(int argc, char* argv[]) {
    imgdata idata;
    imgdata template;
    imgdata ans;

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

		ans.width = template.width;
		ans.height = template.height;

		// 前処理(２値化)
    fixed_threshold(&idata, WHITEVALUE);

		printf("color_depth of f = %d\n", idata.color_depth);
		printf("used_color of f = %d\n", idata.used_color);

		// パターンマッチ
    matching(&idata, &template, &ans_r);

    /* 出力 */
    if (writeBMPfile(argv[3], &ans_r) > 0) {
        printf("Can't save into %s.\n", argv[3]);
        exit(1);
    }

    return 0;
}
