#include "inc/histio.h"

int insertHist(FILE* file, FILE* index, hist x)
{
    if (file == NULL || index == NULL)
        return FAIL_INVALID_FILE;

    if (searchHistGivenPkey(file, index, x.chave) == SUCCESS_FOUND)
        return FAIL_DUPLICATE_HIST;

    // Inserção do registro no arquivo principal (nada de novo aqui)
    int regsize, offset;
    char buffer[HIST_BUFFER_SIZE];
    parseHistIntoBuffer(x, buffer, &regsize);
    fseek(file, 0, SEEK_END);
    offset = ftell(file); // Deslocamento para achar o arquivo depois
    fwrite(&regsize, sizeof(int), 1, file);
    fwrite(buffer, sizeof(char), regsize, file);

    // Inserção da chave no indice primário
    // TODO: modificar a arvore B
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

int searchHistGivenPkey(FILE* file, FILE* index, pkey key)
{
    // TODO: modificar a arvore B
}

int printAllHists(FILE* file, FILE* index)
{
    // TODO: modificar a arvore B
}

int printAllHistsGivenSigla(FILE* file, FILE* index, char sigla[4])
{
    // TODO: modificar a arvore B
}