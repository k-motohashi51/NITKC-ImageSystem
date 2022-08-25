#include <stdio.h>
#include "../inc/matching.h"
#include "../inc/general.h"

void matching(imgdata* F, imgdata* T, imgdata* A) {
	//double pcor, psim, pdist;	// 注目画素の結果
	//double cor, sim, dist;	// 最高の結果
	imgdata pivot;

	pivot.width = T->width;
	pivot.height = T->height;

	printf("pivot.(w, h) = (%d, %d)\n", pivot.width, pivot.height);

	for (int y = 0; y < F->height; y++) {
		for (int x = 0; x < F->width; x++) {
			
		}
	}
}
