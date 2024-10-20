/*
    Definição de funções para manipulação do historico
*/

#ifndef HIST_H
#define HIST_H

typedef struct
{
    char id[4];
    char sigla[4];
} pkey;

typedef struct
{
    pkey chave;
    char nomealuno[50];
    char nomedisciplina[50];
    float media;
    float freq;
} hist;

#define HIST_PRIMARY_INDEX_SIZE sizeof(pkey)
#define HIST_REGISTER_SIZE sizeof(hist)
#define HIST_BUFFER_SIZE 200

#include "base.h"
#include <stdio.h>
#include <string.h>

void printPkey(pkey x);
void printHist(hist x);
int comparePkey(pkey a, pkey b);
int compareHist(hist a, hist b);
void parseHistIntoBuffer(hist x, char * result, int * regsize);
void parseBufferIntoHist(hist * x, char * buffer);

#endif