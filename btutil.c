/*
btutil.c
Contains utility function for btree program
*/
#include "inc/bt.h"

short create_root(char key, short left, short right)
{
    BTPAGE page;

    short rrn;
    rrn = getpage();
    pageinit(&page);
    page.key[0] = key;
    page.child[0] = left;
    page.child[1] = right;
    page.keycount = 1;
    btwrite(rrn, &page);
    putroot(rrn);
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

int search_node(char key, BTPAGE *p_page, short *pos)
{
    int i;
    for (i = 0; i < p_page->keycount && key > p_page->key[i]; i++)
        ;
    *pos = i;
    if (*pos < p_page->keycount && key == p_page->key[*pos])
    {
        return (YES);
    }
    else
    {
        return (NO);
    }
}
void ins_in_page(char key, short r_child, BTPAGE *p_page)
{
    int j;
    for (j = p_page->keycount; key < p_page->key[j - 1] && j > 0; j--)
    {
        p_page->key[j] = p_page->key[j - 1];
        p_page->child[j + 1] = p_page->child[j];
    }
    p_page->keycount++;
    p_page->key[j] = key;
    p_page->child[j + 1] = r_child;
}
void split(char key, short r_child, BTPAGE *p_oldpage, char *promo_key, short *promo_r_child, BTPAGE *p_newpage)
{
    int j;
    short mid;
    char workkeys[MAXKEYS + 1];

    short workchil[MAXKEYS + 2];
    for (j = 0; j < MAXKEYS; j++)
    {
        workkeys[j] = p_oldpage->key[j];
        workchil[j] = p_oldpage->child[j];
    }
    workchil[j] = p_oldpage->child[j];
    for (j = MAXKEYS; key < workkeys[j - 1] && j > 0; j--)
    {
        workkeys[j] = workkeys[j - 1];
        workchil[j + 1] = workchil[j];
    }
    workkeys[j] = key;
    workchil[j + 1] = r_child;
    *promo_r_child = getpage();
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