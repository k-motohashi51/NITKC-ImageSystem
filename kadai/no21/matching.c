#include <stdio.h>
#include <math.h>
#include "./inc/matching.h"

int match(imgdata* f, imgdata* t, imgdata* ra, imgdata* sa, imgdata* da) {
    
}

/* 相関係数 */
double R(imgdata* F, imgdata* T) {
    double cov_ft;
    double dev_f, dev_t;

    cov_ft = s(F, T);
    dev_f = dev(F);
    dev_t = dev(T);

    return (cov_ft / (dev_f * dev_t));
}

/* 標準偏差 */
double dev(imgdata* idata) {
    int sum = 0;

    for (int l = 0; l < idata->height; l++) {
        for (int k = 0; k < idata->width; k++) {
            sum += pow(idata->source[l][k], 2.0);
        }
    }

    return sqrt(sum);
}

/* 類似度 */
double s(imgdata* f, imgdata* t) {
    int sum = 0;

    for (int l = 0; l < t->height; l++) {
        for(int k = 0; k < t->width; k++) {
            sum += f->source[l][k] * t->source[l][k];      
        }
    }

    return sum;
}

/* 距離 */
double d(imgdata* f, imgdata* t) {
    double sum = 0;

    for (int l = 0; l < t->height; l++) {
        for (int k = 0; k < t->width; k++) {
            sum += fabs(f->source[l][k] - t->source[l][k]);
        }
    }

    return sum;
}
