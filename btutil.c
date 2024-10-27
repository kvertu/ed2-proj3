/*
btutil.c
Contains utility function for btree program
*/
#include "inc/bt.h"

pkey pkeyInit(char id[4], char sigla[4])
{
    pkey result;
    strncpy(result.id, id, 4);
    strncpy(result.sigla, sigla, 4);
    return result;
}

short create_root(FILE* index, pkey key, int offset, short left, short right)
{
    BTPAGE page;

    short rrn;
    rrn = getpage(index);
    pageinit(&page);
    page.keys[0] = key;
    page.offsets[0] = offset;
    page.child[0] = left;
    page.child[1] = right;
    page.keycount = 1;
    btwrite(index, rrn, &page);
    putroot(index, rrn);
    return (rrn);
}

void pageinit(BTPAGE *p_page)
{
    int j;
    for (j = 0; j < MAXKEYS; j++)
    {
        p_page->keys[j] = NOKEY;
        p_page->offsets[j] = NIL;
        p_page->child[j] = NIL;
    }
    p_page->child[MAXKEYS] = NIL;
}

int search_node(pkey key, BTPAGE *p_page, short *pos)
{
    int i;
    for (i = 0; i < p_page->keycount && comparePkey(key, p_page->keys[i]) > 0; i++)
        ;
    *pos = i;
    if (*pos < p_page->keycount && comparePkey(key, p_page->keys[*pos]) == 0)
    {
        return (YES);
    }
    else
    {
        return (NO);
    }
}

void ins_in_page(pkey key, int offset, short r_child, BTPAGE *p_page)
{
    int j;
    for (j = p_page->keycount; comparePkey(key, p_page->keys[j - 1]) < 0 && j > 0; j--)
    {
        p_page->keys[j] = p_page->keys[j - 1];
        p_page->offsets[j] = p_page->offsets[j - 1];
        p_page->child[j + 1] = p_page->child[j];
    }
    p_page->keycount++;
    p_page->keys[j] = key;
    p_page->offsets[j] = offset;
    p_page->child[j + 1] = r_child;
}

void split(FILE* index, pkey key, int offset, short r_child, BTPAGE *p_oldpage, pkey *promo_key, int *promo_offset, short *promo_r_child, BTPAGE *p_newpage)
{
    int j;
    pkey workkeys[MAXKEYS + 1];
    int workoffsets[MAXKEYS + 1];
    short workchil[MAXKEYS + 2];

    for (j = 0; j < MAXKEYS; j++)
    {
        workkeys[j] = p_oldpage->keys[j];
        workoffsets[j] = p_oldpage->offsets[j];
        workchil[j] = p_oldpage->child[j];
    }
    workchil[j] = p_oldpage->child[j];

    for (j = MAXKEYS; j > 0 && comparePkey(key, workkeys[j - 1]) < 0; j--)
    {
        workkeys[j] = workkeys[j - 1];
        workoffsets[j] = workoffsets[j - 1];
        workchil[j + 1] = workchil[j];
    }

    workkeys[j] = key;
    workoffsets[j] = offset;
    workchil[j + 1] = r_child;
    *promo_r_child = getpage(index);
    pageinit(p_newpage);

    int midpoint = (MAXKEYS + 1) / 2; // Indice da chave que será promovida

    int i;
    for (i = 0, j = 0; i < midpoint; i++, j++)
    {
        p_oldpage->keys[i] = workkeys[j];
        p_oldpage->offsets[i] = workoffsets[j];
        p_oldpage->child[i] = workchil[j];
    }
    p_oldpage->child[i] = workchil[j];

    for (i = 0, j = j + 1; i < MAXKEYS + 1 - midpoint; i++, j++)
    { 
        p_newpage->keys[i] = workkeys[j];
        p_newpage->offsets[i] = workoffsets[j];
        p_newpage->child[i] = workchil[j];
    }
    p_newpage->child[i] = workchil[j];

    p_newpage->keycount = MAXKEYS - i;
    p_oldpage->keycount = i;
    *promo_key = workkeys[midpoint];
    *promo_offset = workoffsets[midpoint];
    printf("Chave %s%s promovida.\n", workkeys[midpoint].id, workkeys[midpoint].sigla);
}