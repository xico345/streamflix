#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "content.h"

#define INITIAL_CAPACITY 10

/* As variáveis globais serão definidas em main.c */
extern Content *contents;
extern int contentsCount;
extern int contentsCapacity;

int findContentIndexById(int id) {
    for (int i = 0; i < contentsCount; i++) {
        if (contents[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addContent() {
    if (contentsCount >= contentsCapacity) {
        contentsCapacity = (contentsCapacity == 0) ? INITIAL_CAPACITY : contentsCapacity * 2;
        contents = realloc(contents, contentsCapacity * sizeof(Content));
    }
    Content newContent;
    newContent.id = (contentsCount > 0) ? contents[contentsCount - 1].id + 1 : 1;

    printf("Título: ");
    getchar(); // Limpar buffer
    fgets(newContent.titulo, MAX_TITULO, stdin);
    newContent.titulo[strcspn(newContent.titulo, "\n")] = '\0';

    printf("Categoria: ");
    fgets(newContent.categoria, MAX_CATEGORIA, stdin);
    newContent.categoria[strcspn(newContent.categoria, "\n")] = '\0';

    printf("Duração (minutos): ");
    scanf("%d", &newContent.duracao);

    printf("Classificação etária: ");
    scanf("%d", &newContent.faixa_etaria);

    newContent.visualizacoes = 0;

    contents[contentsCount++] = newContent;
    printf("Conteúdo adicionado com sucesso com o ID %d!\n", newContent.id);
}

void removeContent() {
    int id;
    printf("ID do conteúdo a remover: ");
    scanf("%d", &id);

    int index = findContentIndexById(id);
    if (index == -1) {
        printf("Conteúdo com ID %d não encontrado.\n", id);
        return;
    }
    // Remove movendo os elementos seguintes para sobrepor o removido
    for (int i = index; i < contentsCount - 1; i++) {
        contents[i] = contents[i + 1];
    }
    contentsCount--;
    printf("Conteúdo removido com sucesso.\n");
}

void editContent() {
    int id;
    printf("ID do conteúdo a editar: ");
    scanf("%d", &id);

    int index = findContentIndexById(id);
    if (index == -1) {
        printf("Conteúdo com ID %d não encontrado.\n", id);
        return;
    }
    Content *c = &contents[index];
    printf("Editando conteúdo [%d] %s:\n", c->id, c->titulo);

    printf("Novo Título (atual: %s): ", c->titulo);
    getchar(); // Limpar buffer
    fgets(c->titulo, MAX_TITULO, stdin);
    c->titulo[strcspn(c->titulo, "\n")] = '\0';

    printf("Nova Categoria (atual: %s): ", c->categoria);
    fgets(c->categoria, MAX_CATEGORIA, stdin);
    c->categoria[strcspn(c->categoria, "\n")] = '\0';

    printf("Nova Duração (atual: %d): ", c->duracao);
    scanf("%d", &c->duracao);

    printf("Nova Classificação etária (atual: %d): ", c->faixa_etaria);
    scanf("%d", &c->faixa_etaria);

    printf("Conteúdo atualizado com sucesso.\n");
}

void searchContent() {
    int option;
    printf("Pesquisar por:\n1 - Título\n2 - Categoria\n3 - Classificação Etária\nOpção: ");
    scanf("%d", &option);

    char criterio[100];
    int faixa, found = 0;
    getchar(); // Limpar buffer

    if (option == 1) {
        printf("Título (ou parte dele): ");
        fgets(criterio, sizeof(criterio), stdin);
        criterio[strcspn(criterio, "\n")] = '\0';

        for (int i = 0; i < contentsCount; i++) {
            if (strstr(contents[i].titulo, criterio) != NULL) {
                printf("ID: %d | %s | %s | %d min | %d+ | %d visualizações\n",
                       contents[i].id, contents[i].titulo, contents[i].categoria,
                       contents[i].duracao, contents[i].faixa_etaria, contents[i].visualizacoes);
                found++;
            }
        }
    } else if (option == 2) {
        printf("Categoria: ");
        fgets(criterio, sizeof(criterio), stdin);
        criterio[strcspn(criterio, "\n")] = '\0';

        for (int i = 0; i < contentsCount; i++) {
            if (strstr(contents[i].categoria, criterio) != NULL) {
                printf("ID: %d | %s | %s | %d min | %d+ | %d visualizações\n",
                       contents[i].id, contents[i].titulo, contents[i].categoria,
                       contents[i].duracao, contents[i].faixa_etaria, contents[i].visualizacoes);
                found++;
            }
        }
    } else if (option == 3) {
        printf("Classificação etária (número): ");
        scanf("%d", &faixa);
        for (int i = 0; i < contentsCount; i++) {
            if (contents[i].faixa_etaria == faixa) {
                printf("ID: %d | %s | %s | %d min | %d+ | %d visualizações\n",
                       contents[i].id, contents[i].titulo, contents[i].categoria,
                       contents[i].duracao, contents[i].faixa_etaria, contents[i].visualizacoes);
                found++;
            }
        }
    } else {
        printf("Opção inválida.\n");
        return;
    }
    if (found == 0)
        printf("Nenhum conteúdo encontrado.\n");
}