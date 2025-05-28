#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recommendations.h"
#include "content.h"
#include "interactions.h"

void generateRecommendations() {
    char username[MAX_USERNAME];
    printf("Username para recomendações: ");
    getchar();
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';
    
    // Procura a primeira interação do utilizador
    int userContentId = -1;
    for (int i = 0; i < interactionsCount; i++) {
        if (strcmp(interactions[i].username, username) == 0) {
            userContentId = interactions[i].content_id;
            break;
        }
    }
    if (userContentId == -1) {
        printf("Utilizador %s não possui histórico de visualização.\n", username);
        return;
    }
    
    int index = findContentIndexById(userContentId);
    if (index == -1) {
        printf("Histórico inconsistente.\n");
        return;
    }
    char *categoriaPreferida = contents[index].categoria;
    
    printf("Recomendações para %s (Categoria: %s):\n", username, categoriaPreferida);
    for (int i = 0; i < contentsCount; i++) {
        if (strcmp(contents[i].categoria, categoriaPreferida) == 0 &&
            contents[i].id != userContentId) {
            printf("ID: %d | %s\n", contents[i].id, contents[i].titulo);
        }
    }
}