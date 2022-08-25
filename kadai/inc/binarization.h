#ifndef BINARIZATION_H_
#define	BINARIZATION_H_

#include "def.h"
#include "var.h"
#include "bmpfile.h"
#include "histgram.h"

int fixed_threshold(imgdata*, int);
int mode(imgdata*);
int variable_threshold(imgdata*, int);
void expand(imgdata*, int);      // 膨張
void contract(imgdata*, int);    // 収縮

#endif // BINARIZATION_H_
