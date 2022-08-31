#include <stdio.h>
#include <stdlib.h>
#include "../inc/binarization.h"
#include "../inc/bmpfile.h"

int main(int argc, char* argv[]) {
	imgdata idata;

	if (argc < 3) {
		printf("usage: main in17.bmp ans17.bmp\n");
		exit(1);
	}

	if (readBMPfile(argv[1], &idata) > 0) {
		printf("[%s] wasn't found\n", argv[1]);
		exit(1);
	}

	variable_threshold(&idata);

	if (writeBMPfile(argv[2], &idata) > 0) {
		printf("Can't save into %s.\n", argv[1]);
		exit(1);
	}

	return 0;
}
