/* btio.c
Contains btree functions that directly involve file I/O:
*/

#include <stdio.h>
#include <stdlib.h>
#include "inc/bt.h"
// #include "fileio.h"

FILE* btfd; // global file descriptor for "btree.dat"

int btopen()
{
    btfd = fopen("btree.dat", "r+b");
    return btfd != NULL;
}

void btclose()
{
    fclose(btfd);
}

short getroot()
{
    short root;
    
    fseek(btfd, 0, SEEK_SET);;

    if (fread(&root, sizeof(short), 1, btfd) == 0)
    {
        printf("Error: Unable to get root. \007\n");
        exit(1);
    }

    return root;
}

void putroot(short root)
{
    fseek(btfd, 0, SEEK_SET);
    fwrite(&root, sizeof(short), 1, btfd);
}

short create_tree()
{
    char key;

    btfd = fopen("btree.dat", "w+b");
    short temp = -1; // Header temporário para garantir que o código não vai quebrar
    fwrite(&temp, sizeof(short), 1, btfd);
    fclose(btfd);

    btopen();
    key = getchar();

    return create_root(key, NIL, NIL);
}

short getpage()
{
    long addr;
    fseek(btfd, 0, SEEK_END); // sizeof(short) é o cabeçalho do arquivo
    addr = ftell(btfd) - sizeof(short);
    return ((short)addr / PAGESIZE);
}

long btread(short rrn, BTPAGE *page_ptr)
{
    long addr;
    addr = (long)rrn * (long)PAGESIZE + sizeof(short);
    fseek(btfd, addr, SEEK_SET);
    return fread(page_ptr, PAGESIZE, 1, btfd);
}

long btwrite(short rrn, BTPAGE *page_ptr)
{
    long addr;
    addr = (long)rrn * (long)PAGESIZE + sizeof(short);
    fseek(btfd, addr, SEEK_SET);
    return fwrite(page_ptr, PAGESIZE, 1, btfd);
}