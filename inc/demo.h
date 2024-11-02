#ifndef DEMO_H
#define DEMO_H

#include <stdio.h>
#include "hist.h"
#include "histio.h"
#include "bt.h"

void insertFromInsereBin(char * inserebin, char * filename, int first, int amount)
{
    FILE *in = fopen(inserebin, "r+b");

    if (!in)
        return;

    hist entries[amount];
    fseek(in, first * sizeof(hist), SEEK_SET);
    fread(&entries, sizeof(hist), amount, in);
    fclose(in);

    char indexname[FILENAME_MAX];
    sprintf(indexname, "%s.pidx", filename);

    FILE *file = fopen(filename, "r+b");
    FILE *index;
    btopen(&index, indexname);

    if (!file)
    {
        file = fopen(filename, "w+b");
        if (!file)
            return;
    }
    if (!index)
    {
        create_empty_tree(&index, indexname);
        if (!index)
            return;
    }

    for (int i = 0; i < amount; i++)
    {
        insertHist(file, index, entries[i]);
    }

    printf("\n\n=-=-=-=-=\n\n\n");

    btprint(index, file, getroot(index));
    btclose(index);
    fclose(file);
}

void searchFromBuscaBin(char * buscabin, char * filename, int first, int amount)
{
    FILE *in = fopen(buscabin, "r+b");

    if (!in)
        return;

    pkey entries[amount];
    fseek(in, first * sizeof(pkey), SEEK_SET);
    fread(&entries, sizeof(pkey), amount, in);
    fclose(in);

    char indexname[FILENAME_MAX];
    sprintf(indexname, "%s.pidx", filename);

    FILE *file = fopen(filename, "r+b");
    FILE *index;
    btopen(&index, indexname);

    if (!file)
    {
        return;
    }
    if (!index)
    {
        return;
    }

    // for (int i = 0; i < amount; i++)
    // {
    //     printPkey(entries[i]);
    // }

    printf("\n\n=-=-=-=-=\n\n\n");

    for (int i = 0; i < amount; i++)
    {
        btprint_aluno(index, file, getroot(index), entries[i]);
    }
    btclose(index);
    fclose(file);
}

#endif