#include <stdio.h>
#include <stdlib.h>
#include "../inc/bmpfile.h"
#include "../inc/var.h"
#include "../inc/def.h"
#include "../inc/noise_removal.h"

void source2cwork(imgdata*);
void cwork2results(imgdata*);

int main(int argc, char* argv[]) {
	imgdata idata;

	if (argc < 5) {
		printf("usage：main in19.bmp ans19-{1..4}.bmp\n");
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("[%s] wasn't found\n", argv[1]);
		exit(1);
	}

	// 19-1
	source2cwork(&idata);
	expand(&idata, 4);
	contract(&idata, 4);
	contract(&idata, 4);
	expand(&idata, 4);
	cwork2results(&idata);

	if (writeBMPfile(argv[2], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	// 19-2
	source2cwork(&idata);
	contract(&idata, 4);
	expand(&idata, 4);
	expand(&idata, 4);
	contract(&idata, 4);
	cwork2results(&idata);

	if (writeBMPfile(argv[3], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	// 19-3
	source2cwork(&idata);
	expand(&idata, 8);
	contract(&idata, 8);
	contract(&idata, 8);
	expand(&idata, 8);
	cwork2results(&idata);

	if (writeBMPfile(argv[4], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	// 19-4
	source2cwork(&idata);
	contract(&idata, 8);
	expand(&idata, 8);
	expand(&idata, 8);
	contract(&idata, 8);
	cwork2results(&idata);

	if (writeBMPfile(argv[5], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	return 0;
}

void source2cwork(imgdata* idata) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			idata->cwork[RED][y][x] = idata->source[RED][y][x];
			idata->cwork[GREEN][y][x] = idata->source[GREEN][y][x];
			idata->cwork[BLUE][y][x] = idata->source[BLUE][y][x];
		}
	}
}

void cwork2results(imgdata* idata) {
	for (int y = 0; y < idata->height; y++) {
		for (int x = 0; x < idata->width; x++) {
			idata->results[RED][y][x] = idata->cwork[RED][y][x];
			idata->results[GREEN][y][x] = idata->cwork[GREEN][y][x];
			idata->results[BLUE][y][x] = idata->cwork[BLUE][y][x];
		}
	}
}
