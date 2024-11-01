#ifndef HISTIO_H
#define HISTIO_H

#include <stdio.h>
#include <stdlib.h>
#include "hist.h"
#include "base.h"

int insertHist(FILE* file, FILE* index, hist x);
int getHist(FILE* file, int offset, hist * result);
int insertIndex(FILE* index, hist x, int offset);

#endif