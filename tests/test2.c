/* driver.c
Driver for btree tests
Open or creates b-tree file.
Get next key and calls insert to insert key in tree.
If necessary creates new root.
*/

#include "../inc/bt.h"

int main()
{
    FILE* in;
    short root;

    if (btopen(&in, "teste.pidx"))
        root = getroot(in);
    else
    {
        printf("Deu ruim!\n");
        return 1;
    }

    pkey key = {"001", "BBB"};
    btprint(in, root);
    printf("\n");
    btprint_aluno(in, root, key);

    btclose(in);
    return 0;
}