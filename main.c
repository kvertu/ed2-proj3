#include "inc/demo.h"

void helper()
{
    printf("\nSelecione uma opção:\n0. Sair\n1. Inserir\n2. Imprimir\n3. Buscar\n\n");
}

void error()
{
    printf("Opção inválida, tente novamente.\n");
}

int main()
{
    printf("=-=-= Projeto III - ED2 =-=-=\n");
    int choice;

    char file[FILENAME_MAX];
    char ext[FILENAME_MAX];
    int first, amount;

    do {
        helper();
        scanf(" %d", &choice);

        switch (choice)
        {
        case 0:
            printf("Saindo...\n");
            break;

        case 1:
            printf("Informe o nome do arquivo a ser inserido: ");
            scanf(" %s", file);
            printf("Informe o nome do arquivo de onde vai vir os dados (insere.bin): ");
            scanf(" %s", ext);
            printf("Informe o indice da primeira entrada: ");
            scanf(" %d", &first);
            printf("Informe a quantidade de entradas a ser lida: ");
            scanf(" %d", &amount);
            insertFromInsereBin(ext, file, first, amount);
            break;

        case 2:
            printf("Informe o nome do arquivo a ser impresso: ");
            scanf(" %s", file);
            printAllHists(file);
            break;

        case 3:
            printf("Informe o nome do arquivo a ser buscado: ");
            scanf(" %s", file);
            printf("Informe o nome do arquivo de onde vai vir os dados (busca.bin): ");
            scanf(" %s", ext);
            printf("Informe o indice da primeira entrada: ");
            scanf(" %d", &first);
            printf("Informe a quantidade de entradas a ser lida: ");
            scanf(" %d", &amount);
            searchFromBuscaBin(ext, file, first, amount);
            break;

        default:
            error();
            break;
        }
    } while (choice != 0);

    return 0;
}