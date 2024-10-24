#include "inc/hist.h"
#include <stdlib.h>

void printPkey(pkey x)
{
    printf("Chave: %s%s\n", x.id, x.sigla);
}

void printHist(hist x)
{
    printPkey(x.chave);
    printf("Nome: %s\nDisciplina: %s\nMédia: %f\nFrequência: %f\n", x.nomealuno, x.nomedisciplina, x.media, x.freq);
}

int comparePkey(pkey a, pkey b)
{
    char buffera[7], bufferb[7];
    sprintf(buffera, "%s%s", a.id, a.sigla);
    sprintf(bufferb, "%s%s", b.id, b.sigla);
    return strcmp(buffera, bufferb);
}

int compareHist(hist a, hist b)
{
    return comparePkey(a.chave, b.chave);
}

void parseHistIntoBuffer(hist x, char * result, int * regsize)
{
    sprintf(result, "%s#%s#%s#%s#%f#%f", x.chave.id, x.chave.sigla, x.nomealuno, x.nomedisciplina, x.media, x.freq);
    (*regsize) = strlen(result) + 1;
}

void parseBufferIntoHist(hist * x, char * buffer)
{
    char * temp = strtok(buffer, "#");
    strncpy(x->chave.id, temp, 4);
    temp = strtok(NULL, "#");
    strncpy(x->chave.sigla, temp, 4);
    temp = strtok(NULL, "#");
    strcpy(x->nomealuno, temp);
    temp = strtok(NULL, "#");
    strcpy(x->nomedisciplina, temp);
    temp = strtok(NULL, "#");
    x->media = atof(temp);
    temp = strtok(NULL, "#");
    x->freq = atof(temp);
}