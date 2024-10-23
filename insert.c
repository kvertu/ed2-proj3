/* insert.c
Contains insert() function to insert a key into a btree.
Calls itself recursively until bottom of tree is reached.
Then insert key node.
If node is out of room,
- calls split() to split node
- promotes middle key and rrn of new node
*/

#include <stdio.h>
#include "inc/bt.h"

int insert(FILE* index, short rrn, pkey_woffset key, short *promo_r_child, pkey_woffset *promo_key)
{
    BTPAGE page,         // current page
        newpage;         // new page created if split occurs

    int found, promoted; // boolean values

    short pos,
        p_b_rrn;  // rrn promoted from below

    pkey_woffset p_b_key; // key promoted from below

    if (rrn == NIL)
    {
        *promo_key = key;
        *promo_r_child = NIL;
        return (YES);
    }

    btread(index, rrn, &page);
    found = search_node(key.primary, &page, &pos);
    if (found)
    {
        printf("Error: attempt to insert duplicate key:\n");
        printPkey(key.primary);
        return 0;
    }

    promoted = insert(index, page.child[pos], key, &p_b_rrn, &p_b_key);
    if (!promoted)
    {
        return NO;
    }

    if (page.keycount < MAXKEYS)
    {
        ins_in_page(p_b_key, p_b_rrn, &page);
        btwrite(index, rrn, &page);
        return NO;
    }
    else
    {
        split(index, p_b_key, p_b_rrn, &page, promo_key, promo_r_child, &newpage);
        btwrite(index, rrn, &page);
        btwrite(index, *promo_r_child, &newpage);
        return YES;
    }
}