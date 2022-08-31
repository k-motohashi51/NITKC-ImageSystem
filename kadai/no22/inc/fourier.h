#ifndef FOURIER_H_
#define FOURIER_H_

typedef struct {
	double re;
	double im;
} complex_t;

void DFT(complex_t c[], int, FILE*);

#endif
