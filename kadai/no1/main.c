#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int main(int argc, char *argv[])
{
    imgdata idata;
    double Y = 0;
    
    if (argc < 3) {
       printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
    } else if (readBMPfile(argv[1], &idata) > 0) {
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    } else {
    }

    for (int i = 0; i < idata.height; i++) {
        for (int j = 0; j < idata.width; j++) {
            Y = 0.299 * idata.source[RED][j][i] 
                + 0.587 * idata.source[GREEN][j][i] 
                + 0.114 * idata.source[BLUE][j][i];

            idata.results[RED][j][i] = Y;
            idata.results[GREEN][j][i] = Y;
            idata.results[BLUE][j][i] = Y;
        }
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }

    return 0;
}
