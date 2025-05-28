#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

/* Definição de um tamanho inicial para alocação dinâmica */
#define INITIAL_CAPACITY 10

/* As variáveis globais para armazenar conteúdos e interações */
extern Content *contents;
extern int contentsCount;
extern int contentsCapacity;

extern Interaction *interactions;
extern int interactionsCount;
extern int interactionsCapacity;

void readContentsFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Não foi possível abrir o ficheiro %s para leitura de conteúdos.\n", filename);
        return;
    }
    char linha[256];
    // Ignorar cabeçalho
    fgets(linha, sizeof(linha), file);
    while (fgets(linha, sizeof(linha), file)) {
        if (contentsCount >= contentsCapacity) {
            contentsCapacity = (contentsCapacity == 0) ? INITIAL_CAPACITY : contentsCapacity * 2;
            contents = realloc(contents, contentsCapacity * sizeof(Content));
        }
        Content newContent;
        // CSV: id,titulo,categoria,duracao,faixa_etaria,visualizacoes
        sscanf(linha, "%d,%99[^,],%49[^,],%d,%d,%d",
               &newContent.id, newContent.titulo, newContent.categoria,
               &newContent.duracao, &newContent.faixa_etaria, &newContent.visualizacoes);
        contents[contentsCount++] = newContent;
    }
    fclose(file);
}

void writeContentsToCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Não foi possível abrir o ficheiro %s para escrita de conteúdos.\n", filename);
        return;
    }
    // Cabeçalho
    fprintf(file, "id,titulo,categoria,duracao,faixa_etaria,visualizacoes\n");
    for (int i = 0; i < contentsCount; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%d\n",
                contents[i].id,
                contents[i].titulo,
                contents[i].categoria,
                contents[i].duracao,
                contents[i].faixa_etaria,
                contents[i].visualizacoes);
    }
    fclose(file);
}

void readInteractionsFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Não foi possível abrir o ficheiro %s para leitura de interações.\n", filename);
        return;
    }
    char linha[256];
    // Ignorar cabeçalho
    fgets(linha, sizeof(linha), file);
    while (fgets(linha, sizeof(linha), file)) {
        if (interactionsCount >= interactionsCapacity) {
            interactionsCapacity = (interactionsCapacity == 0) ? INITIAL_CAPACITY : interactionsCapacity * 2;
            interactions = realloc(interactions, interactionsCapacity * sizeof(Interaction));
        }
        Interaction newInter;
        // CSV: username,content_id,acao
        sscanf(linha, "%49[^,],%d,%19[^\n]", newInter.username, &newInter.content_id, newInter.acao);
        interactions[interactionsCount++] = newInter;
    }
    fclose(file);
}

void writeInteractionsToCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Não foi possível abrir o ficheiro %s para escrita de interações.\n", filename);
        return;
    }
    // Cabeçalho
    fprintf(file, "username,content_id,acao\n");
    for (int i = 0; i < interactionsCount; i++) {
        fprintf(file, "%s,%d,%s\n",
                interactions[i].username,
                interactions[i].content_id,
                interactions[i].acao);
    }
    fclose(file);
}