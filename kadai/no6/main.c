#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"
#include "density_convertion.h"

#define E_SUCCESS 0

int convert_density(imgdata*);

int main(int argc, char* argv[]) {
    imgdata idata;

    if (argc < 3) {
        printf("usage：main in8.bmp ans8.bmp\n");
        exit(1);
    }
    
    if (readBMPfile(argv[1], &idata) > 0) {
        printf("[%s] wasn't found\n", argv[1]);
        exit(1);
    }

    if (convert_density(&idata) != E_SUCCESS) {
        printf("ERROR!\n");
        exit(1);
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
        printf("Can't save into %s.\n", argv[1]);
        exit(1);
    }

    return 0;
}

int convert_density(imgdata* idata) {
	int LUT[Z_MAX + 1];

	for (int i = 0; i < Z_MAX + 1; i++) {
		LUT[i] = root(i);
	}

    for (int y = 0; y < idata->height; y++) {
        for (int x = 0; x < idata->width; x++) {
            idata->results[RED][y][x] = LUT[idata->source[RED][y][x]];
            idata->results[GREEN][y][x] = LUT[idata->source[GREEN][y][x]];
            idata->results[BLUE][y][x] = LUT[idata->source[BLUE][y][x]];
        }
    }

    return E_SUCCESS;
}
