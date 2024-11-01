#include "../inc/histio.h"
#include "../inc/bt.h"

int main()
{
    hist x;
    x.chave = pkeyInit("001", "AAA");
    strcpy(x.nomealuno, "Fulano de Tal");
    strcpy(x.nomedisciplina, "Disciplina");
    x.media = 9.f;
    x.freq = 99.f;
    printHist(x);
    
    FILE *file, *index;

    file = fopen("exemplo.bin", "w+b");
    create_empty_tree(&index, "exemplo.pidx");
    
    insertHist(file, index, x);
    btprint(index, getroot(index));

    return 0;
}