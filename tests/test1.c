/* driver.c
Driver for btree tests
Open or creates b-tree file.
Get next key and calls insert to insert key in tree.
If necessary creates new root.
*/

#include "../inc/bt.h"

pkey_woffset readPkeyWO(char id[4], char sigla[4], int offset)
{
    pkey_woffset x;
    strncpy(x.primary.id, id, 4);
    strncpy(x.primary.sigla, sigla, 4);
    x.offset = offset;
    return x;
}


int main()
{
    int promoted;   // boolean: tells if a promotion from below
    short root,     // rrn of root page
        promo_rrn;  // rrn promoted from below
    pkey_woffset promo_key, // key promoted from below
        key;        // next key to insert in tree

    FILE* in;

    char id[4], sigla[4];
    int offset;

    if (btopen(&in))
    {
        root = getroot(in);
    }
    else
    {
        scanf(" %s", id);
        scanf(" %s", sigla);
        scanf(" %d", &offset);

        root = create_tree(&in, "teste.pidx", readPkeyWO(id, sigla, offset));
    }

    scanf(" %s", id);
    scanf(" %s", sigla);
    scanf(" %d", &offset);
    key = readPkeyWO(id, sigla, offset);
    while (offset != -2)
    {
        promoted = insert(in, root, key, &promo_rrn, &promo_key);
        if (promoted)
        {
            root = create_root(in, promo_key, root, promo_rrn);
        }
        scanf(" %s", id);
        scanf(" %s", sigla);
        scanf(" %d", &offset);
        key = readPkeyWO(id, sigla, offset);
    }
    btclose(in);
}