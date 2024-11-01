/* btio.c
Contains btree functions that directly involve file I/O:
*/

#include <stdio.h>
#include <stdlib.h>
#include "inc/bt.h"
#include "inc/histio.h"
// #include "fileio.h"

FILE* btfd; // global file descriptor for "btree.dat"

int btopen(FILE** index, char * filename)
{
    (*index) = fopen(filename, "r+b");
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

void create_empty_tree(FILE** index, char * filename)
{
    (*index) = fopen(filename, "w+b");
    short temp = -1; // Header temporário para garantir que o código não vai quebrar
    fwrite(&temp, sizeof(short), 1, (*index));
}

short create_tree(FILE** index, char * filename, pkey key, int offset)
{

    create_empty_tree(index, filename);
    fclose((*index));

    btopen(index, filename);

    return create_root(*index, key, offset, NIL, NIL);
}

short getpage(FILE* index)
{
    long addr;
    fseek(index, 0, SEEK_END); 
    addr = ftell(index) - sizeof(short); // sizeof(short) é o cabeçalho do arquivo
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

void btprint(FILE* index, FILE* file, short rrn)
{
    if (rrn < 0) return;

    int i;
    BTPAGE cur;

    if (!btread(index, rrn, &cur)) return;

    for (i = 0; i < cur.keycount; i++)
    {
        btprint(index, file, cur.child[i]);
        hist res;
        getHist(file, cur.offsets[i], &res);
        printHist(res);
        printf("\n");
    }
    btprint(index, file, cur.child[i]);
}

void btprint_aluno(FILE* index, FILE* file, short rrn, pkey key)
{
    if (rrn < 0) return;

    short i;
    BTPAGE cur;
    if (!btread(index, rrn, &cur)) return;

    if (search_node(key, &cur, &i))
    {
        hist res;
        getHist(file, cur.offsets[i], &res);
        printHist(res);
    }
    else
    {
        btprint_aluno(index, file, cur.child[i], key);
    }
}

int btsearch_aluno(FILE* index, short rrn, pkey key)
{
    if (rrn < 0) return FAIL_NOT_FOUND;

    short i;
    BTPAGE cur;
    if (!btread(index, rrn, &cur)) return FAIL_INVALID_FILE;

    if (search_node(key, &cur, &i))
        return cur.offsets[i];
    else
    {
        return btsearch_aluno(index, cur.child[i], key);
    }
}