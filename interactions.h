#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#define MAX_ACAO 20
#define MAX_USERNAME 50

typedef struct {
    char username[MAX_USERNAME];
    int content_id;
    char acao[MAX_ACAO]; // Ex.: "play", "pause", "finish"
} Interaction;

/* Declaração de variáveis globais para interações */
extern Interaction *interactions;
extern int interactionsCount;
extern int interactionsCapacity;

/* Declaração das funções */
void recordInteraction();
void markAsFavorite();

#endif