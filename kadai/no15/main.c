#include <stdio.h>
#include <stdlib.h>
#include "binarization.h"

int convert_density(imgdata*);

int main(int argc, char* argv[]) {
    imgdata idata;
	int threshold = 50;

    if (argc < 3) {
        printf("usage：main in8.bmp ans8.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("[%s] wasn't found\n", argv[1]);
        exit(1);
    }

    if (fixed_threshold(&idata, threshold) != E_SUCCESS) {
        printf("ERROR!\n");
        exit(1);
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
        exit(1);
    }

    return 0;
}
