#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interactions.h"
#include "content.h"

#define INITIAL_CAPACITY 10

extern Interaction *interactions;
extern int interactionsCount;
extern int interactionsCapacity;
extern Content *contents;
extern int contentsCount;

/* Regista uma interação e atualiza visualizações se a ação for "finish" */
void recordInteraction() {
    Interaction inter;
    printf("Username: ");
    getchar(); // Limpar buffer
    fgets(inter.username, MAX_USERNAME, stdin);
    inter.username[strcspn(inter.username, "\n")] = '\0';

    printf("ID do conteúdo: ");
    scanf("%d", &inter.content_id);

    printf("Ação (play, pause, finish): ");
    scanf("%s", inter.acao);

    if (interactionsCount >= interactionsCapacity) {
        interactionsCapacity = (interactionsCapacity == 0) ? INITIAL_CAPACITY : interactionsCapacity * 2;
        interactions = realloc(interactions, interactionsCapacity * sizeof(Interaction));
    }
    interactions[interactionsCount++] = inter;

    // Atualizar visualizações se a interação for "finish"
    if (strcmp(inter.acao, "finish") == 0) {
        int index = findContentIndexById(inter.content_id);
        if (index != -1)
            contents[index].visualizacoes++;
    }
    printf("Interação registada com sucesso.\n");
}

void markAsFavorite() {
    char username[MAX_USERNAME];
    int content_id;
    printf("Username: ");
    getchar(); // Limpar buffer
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("ID do conteúdo para marcar como favorito: ");
    scanf("%d", &content_id);

    printf("Conteúdo ID %d marcado como favorito para o utilizador %s.\n", content_id, username);
}