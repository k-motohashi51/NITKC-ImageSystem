#include <stdio.h>
#include <stdlib.h>
#include "binarization.h"

int main(int argc, char* argv[]) {
	imgdata idata;
	int variance_base = 1000;

	if (argc < 3) {
		printf("usage: main in17.bmp ans17.bmp\n");
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("[%s] wasn't found\n", argv[1]);
		exit(1);
	}

	if (variable_threshold(&idata, variance_base) != E_SUCCESS) {
		printf("ERROR!\n");
		exit(1);
	}

	if (writeBMPfile(argv[2], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	return 0;
}
