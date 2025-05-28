#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "content.h"
#include "interactions.h"

void reportMostWatched() {
    if (contentsCount == 0) {
        printf("Nenhum conteúdo disponível.\n");
        return;
    }
    // Cria uma cópia dos conteúdos para ordenar
    Content *sorted = malloc(contentsCount * sizeof(Content));
    memcpy(sorted, contents, contentsCount * sizeof(Content));
    // Ordenação simples por visualizações (decrescente)
    for (int i = 0; i < contentsCount - 1; i++) {
        for (int j = 0; j < contentsCount - i - 1; j++) {
            if (sorted[j].visualizacoes < sorted[j+1].visualizacoes) {
                Content temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    printf("Conteúdos mais assistidos:\n");
    for (int i = 0; i < contentsCount; i++) {
        printf("ID: %d | %s | Visualizações: %d\n", sorted[i].id, sorted[i].titulo, sorted[i].visualizacoes);
    }
    free(sorted);
}

void reportPopularCategories() {
    if (contentsCount == 0) {
        printf("Nenhum conteúdo disponível.\n");
        return;
    }
    
    typedef struct {
        char categoria[MAX_CATEGORIA];
        int totalViews;
    } CategoryReport;
    
    CategoryReport reports[50];
    int reportCount = 0;
    memset(reports, 0, sizeof(reports));

    for (int i = 0; i < contentsCount; i++) {
        int found = 0;
        for (int j = 0; j < reportCount; j++) {
            if (strcmp(reports[j].categoria, contents[i].categoria) == 0) {
                reports[j].totalViews += contents[i].visualizacoes;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(reports[reportCount].categoria, contents[i].categoria, MAX_CATEGORIA);
            reports[reportCount].totalViews = contents[i].visualizacoes;
            reportCount++;
        }
    }
    
    printf("Categorias mais populares:\n");
    for (int i = 0; i < reportCount; i++) {
        printf("Categoria: %s | Total de visualizações: %d\n",
               reports[i].categoria, reports[i].totalViews);
    }
}

void reportMostActiveUsers() {
    if (interactionsCount == 0) {
        printf("Nenhuma interação registada.\n");
        return;
    }
    
    typedef struct {
        char username[MAX_USERNAME];
        int count;
    } UserReport;
    
    UserReport users[50];
    int userCount = 0;
    memset(users, 0, sizeof(users));
    
    for (int i = 0; i < interactionsCount; i++) {
        int found = 0;
        for (int j = 0; j < userCount; j++) {
            if (strcmp(users[j].username, interactions[i].username) == 0) {
                users[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(users[userCount].username, interactions[i].username, MAX_USERNAME);
            users[userCount].count = 1;
            userCount++;
        }
    }
    
    printf("Utilizadores mais ativos:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Username: %s | Nº de interações: %d\n", users[i].username, users[i].count);
    }
}