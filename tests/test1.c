/* driver.c
Driver for btree tests
Open or creates b-tree file.
Get next key and calls insert to insert key in tree.
If necessary creates new root.
*/

#include "../inc/bt.h"

pkey readPkey(char id[4], char sigla[4])
{
    pkey x;
    strncpy(x.id, id, 4);
    strncpy(x.sigla, sigla, 4);
    return x;
}


int main()
{
    int promoted;   // boolean: tells if a promotion from below
    short root,     // rrn of root page
        promo_rrn;  // rrn promoted from below
    pkey promo_key, // key promoted from below
        key;        // next key to insert in tree
    int promo_offset,
        offset;

    FILE* in;

    char id[4], sigla[4];

    if (btopen(&in, "teste.pidx"))
    {
        root = getroot(in);
    }
    else
    {
        scanf(" %s", id);
        scanf(" %s", sigla);
        scanf(" %d", &offset);

        root = create_tree(&in, "teste.pidx", readPkey(id, sigla), offset);
        printf("Chave %s%s inserida com sucesso!\n", id, sigla);
    }

    scanf(" %s", id);
    scanf(" %s", sigla);
    scanf(" %d", &offset);
    key = readPkey(id, sigla);
    while (offset != -2)
    {
        promoted = insert(in, root, key, offset, &promo_rrn, &promo_key, &promo_offset);
        if (promoted)
        {
            root = create_root(in, promo_key, promo_offset, root, promo_rrn);
        }
        printf("Chave %s%s inserida com sucesso!\n", id, sigla);
        scanf(" %s", id);
        scanf(" %s", sigla);
        scanf(" %d", &offset);
        key = readPkey(id, sigla);
    }
    btclose(in);
}