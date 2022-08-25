#include <math.h>
#include "../inc/general.h"

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
            sum += pow(idata->source[RED][l][k], 2);
        }
    }

    return sqrt(sum);
}

/* 類似度 */
double s(imgdata* f, imgdata* t) {
    int sum = 0;

    for (int l = 0; l < t->height; l++) {
        for(int k = 0; k < t->width; k++) {
            sum += f->source[RED][l][k] * t->source[RED][l][k];      
        }
    }

    return sum;
}

/* 距離 */
double d(imgdata* f, imgdata* t) {
    double sum = 0;

    for (int l = 0; l < t->height; l++) {
        for (int k = 0; k < t->width; k++) {
            sum += fabs(f->source[RED][l][k] - t->source[RED][l][k]);
        }
    }

    return sum;
}
