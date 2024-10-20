/*
btutil.c
Contains utility function for btree program
*/
#include "inc/bt.h"

pkey_woffset pkeyWOInit(char id[4], char sigla[4], int offset)
{
    pkey_woffset result;
    strncpy(result.primary.id, id, 4);
    strncpy(result.primary.sigla, sigla, 4);
    result.offset = offset;
    return result;
}

short create_root(FILE* index, pkey_woffset key, short left, short right)
{
    BTPAGE page;

    short rrn;
    rrn = getpage(index);
    pageinit(&page);
    page.key[0] = key;
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
        p_page->key[j] = NOKEY;
        p_page->child[j] = NIL;
    }
    p_page->child[MAXKEYS] = NIL;
}

int search_node(pkey key, BTPAGE *p_page, short *pos)
{
    int i;
    for (i = 0; i < p_page->keycount && comparePkey(key, p_page->key[i].primary) > 0; i++)
        ;
    *pos = i;
    if (*pos < p_page->keycount && comparePkey(key, p_page->key[*pos].primary) == 0)
    {
        return (YES);
    }
    else
    {
        return (NO);
    }
}

void ins_in_page(pkey_woffset key, short r_child, BTPAGE *p_page)
{
    int j;
    for (j = p_page->keycount; comparePkey(key.primary, p_page->key[j - 1].primary) < 0 && j > 0; j--)
    {
        p_page->key[j] = p_page->key[j - 1];
        p_page->child[j + 1] = p_page->child[j];
    }
    p_page->keycount++;
    p_page->key[j] = key;
    p_page->child[j + 1] = r_child;
}

void split(FILE* index, pkey_woffset key, short r_child, BTPAGE *p_oldpage, pkey_woffset *promo_key, short *promo_r_child, BTPAGE *p_newpage)
{
    int j;
    short mid;
    pkey_woffset workkeys[MAXKEYS + 1];

    short workchil[MAXKEYS + 2];
    for (j = 0; j < MAXKEYS; j++)
    {
        workkeys[j] = p_oldpage->key[j];
        workchil[j] = p_oldpage->child[j];
    }

    workchil[j] = p_oldpage->child[j];
    for (j = MAXKEYS; comparePkey(key.primary, workkeys[j - 1].primary) < 0 && j > 0; j--)
    {
        workkeys[j] = workkeys[j - 1];
        workchil[j + 1] = workchil[j];
    }

    workkeys[j] = key;
    workchil[j + 1] = r_child;
    *promo_r_child = getpage(index);
    pageinit(p_newpage);
    for (j = 0; j < MINKEYS; j++)
    {
        p_oldpage->key[j] = workkeys[j];
        p_oldpage->child[j] = workchil[j];
        p_newpage->key[j] = workkeys[j + 1 + MINKEYS];
        p_newpage->child[j] = workchil[j + 1 + MINKEYS];
        p_oldpage->key[j + MINKEYS] = NOKEY;
        p_oldpage->child[j + 1 + MINKEYS] = NIL;
    }
    p_oldpage->child[MINKEYS] = workchil[MINKEYS];
    p_newpage->child[MINKEYS] = workchil[j + 1 + MINKEYS];
    p_newpage->keycount = MAXKEYS - MINKEYS;
    p_oldpage->keycount = MINKEYS;
    *promo_key = workkeys[MINKEYS];
}