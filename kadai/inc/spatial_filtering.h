#ifndef SPATIAL_FILTERING_H_
#define SPATIAL_FILTERING_H_ 

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int average(imgdata*, int);
int median(imgdata*);
double calc_median(int*, int);
int prewitt();
int sobel();
int laplacian();
int sharpen();

#endif	// SPATIAL_FILTERING_H_
