#include <math.h>
#include "density_convertion.h"

int quadratic(int z) {
    return (int)(Z_MAX * pow((double)z / Z_MAX, 2.0));
}

int root(int z) {
    return (int)(Z_MAX * sqrt((double)z / Z_MAX));
}

int sigmoid(int z, double a) {
    double sig = 1 / (1 + exp(-a * ((double)z / Z_MAX - 0.5)));

    return (int)(Z_MAX * sig);
}
