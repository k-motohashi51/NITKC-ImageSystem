#include <stdio.h>
#include <stdlib.h>
#include "../inc/binarization.h"

int main(int argc, char* argv[]) {
    imgdata idata;
    imgdata temp;

    if (argc < 3) {
        printf("usage：main in19.bmp ans19.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("[%s] wasn't found\n", argv[1]);
        exit(1);
    }

    temp = idata;

    expand(&temp, 4);
    contract(&idata, 4);
    contract(&idata, 4);
    expand(&idata, 4);

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
        exit(1);
    }

    return 0;
}
