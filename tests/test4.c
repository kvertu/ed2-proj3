#include "../inc/demo.h"

int main()
{
    printf("%ld\n", sizeof(BTPAGE));
    insertFromInsereBin("examples/insere.bin", "out.bin", 0, 11);
    searchFromBuscaBin("examples/busca.bin", "out.bin", 0, 5);

    return 0;
}