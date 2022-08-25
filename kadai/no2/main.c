#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define E_SUCCESS 0

int invert_pixels(imgdata*);

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

    if (invert_pixels(&idata) != E_SUCCESS) {
        printf("ERROR!\n");
        exit(1);
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
        exit(1);
    }

    return 0;
}

int invert_pixels(imgdata* idata) {
    int glv;

    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            glv = idata->source[RED][y][x];
            idata->results[RED][y][x] = 255 - glv;
            glv = idata->source[GREEN][y][x];
            idata->results[GREEN][y][x] = 255 - glv;
            glv = idata->source[BLUE][y][x];
            idata->results[BLUE][y][x] = 255 - glv;
        }
    }

    return E_SUCCESS;
}
