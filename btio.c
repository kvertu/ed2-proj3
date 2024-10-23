/* btio.c
Contains btree functions that directly involve file I/O:
*/

#include <stdio.h>
#include <stdlib.h>
#include "inc/bt.h"
// #include "fileio.h"

FILE* btfd; // global file descriptor for "btree.dat"

int btopen(FILE** index)
{
    (*index) = fopen("btree.dat", "r+b");
    return (*index) != NULL;
}

void btclose(FILE* index)
{
    fclose(index);
}

short getroot(FILE* index)
{
    short root;
    
    fseek(index, 0, SEEK_SET);;

    if (fread(&root, sizeof(short), 1, index) == 0)
    {
        printf("Error: Unable to get root. \007\n");
        exit(1);
    }

    return root;
}

void putroot(FILE* index, short root)
{
    fseek(index, 0, SEEK_SET);
    fwrite(&root, sizeof(short), 1, index);
}

short create_tree(FILE** index, char * filename, pkey_woffset key)
{

    (*index) = fopen(filename, "w+b");
    short temp = -1; // Header temporário para garantir que o código não vai quebrar
    fwrite(&temp, sizeof(short), 1, (*index));
    fclose((*index));

    btopen(index);

    return create_root(*index, key, NIL, NIL);
}

short getpage(FILE* index)
{
    long addr;
    fseek(index, 0, SEEK_END); // sizeof(short) é o cabeçalho do arquivo
    addr = ftell(index) - sizeof(short);
    return ((short)addr / PAGESIZE);
}

long btread(FILE* index, short rrn, BTPAGE *page_ptr)
{
    long addr;
    addr = (long)rrn * (long)PAGESIZE + sizeof(short);
    fseek(index, addr, SEEK_SET);
    return fread(page_ptr, PAGESIZE, 1, index);
}

long btwrite(FILE* index, short rrn, BTPAGE *page_ptr)
{
    long addr;
    addr = (long)rrn * (long)PAGESIZE + sizeof(short);
    fseek(index, addr, SEEK_SET);
    return fwrite(page_ptr, PAGESIZE, 1, index);
}