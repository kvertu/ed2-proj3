#include "inc/histio.h"
#include "inc/bt.h"

int insertIndex(FILE* index, hist x, int offset)
{
    if (index == NULL)
        return FAIL_INVALID_FILE;

    short promo_rrn;
    int promo_offset;
    pkey promo_key;

    short root = getroot(index);
    if (insert(index, root, x.chave, offset, &promo_rrn, &promo_key, &promo_offset))
    {
        short temp = create_root(index, promo_key, promo_offset, root, promo_rrn);
        putroot(index, temp);
    }

    printf("Chave %s%s inserida.\n", x.chave.id, x.chave.sigla);
    return SUCCESS;
}

int insertHist(FILE* file, FILE* index, hist x)
{
    if (file == NULL || index == NULL)
        return FAIL_INVALID_FILE;

    rewind(file);
    rewind(index);

    int test = btsearch_aluno(index, getroot(index), x.chave);
    if (test != -1)
    {
        printf("Chave %s%s é duplicata.\n", x.chave.id, x.chave.sigla);
        return FAIL_DUPLICATE_HIST;
    }

    // Inserção do registro no arquivo principal (nada de novo aqui)
    int regsize, offset;
    char buffer[HIST_BUFFER_SIZE];
    parseHistIntoBuffer(x, buffer, &regsize);
    fseek(file, 0, SEEK_END);
    offset = ftell(file); // Deslocamento para achar o arquivo depois
    fwrite(&regsize, sizeof(int), 1, file);
    fwrite(buffer, sizeof(char), regsize, file);

    // printf("Offset = %d\n", offset);
    // Inserção da chave no indice primário
    if (getroot(index) == -1)
        return create_root(index, x.chave, offset, NIL, NIL);
    else
        return insertIndex(index, x, offset);
}

int getHist(FILE* file, int offset, hist * result)
{
    if (file == NULL)
        return FAIL_INVALID_FILE;
    
    int regsize;
    fseek(file, offset, SEEK_SET);
    fread(&regsize, sizeof(int), 1, file);

    char buffer[regsize];
    fread(buffer, sizeof(char), regsize, file);
    parseBufferIntoHist(result, buffer);

    return SUCCESS;
}