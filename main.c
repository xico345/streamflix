#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "content.h"
#include "interactions.h"
#include "reports.h"
#include "recommendations.h"

/* Definição das variáveis globais */
Content *contents = NULL;
int contentsCount = 0;
int contentsCapacity = 0;

Interaction *interactions = NULL;
int interactionsCount = 0;
int interactionsCapacity = 0;

#define INITIAL_CAPACITY 10

void menu() {
    int opcao;
    char dummy;
    do {
        printf("\n--- Streamflix - Menu Principal ---\n");
        printf("1 - Listar conteúdos\n");
        printf("2 - Adicionar conteúdo\n");
        printf("3 - Remover conteúdo\n");
        printf("4 - Editar conteúdo\n");
        printf("5 - Pesquisar conteúdo\n");
        printf("6 - Registar interação\n");
        printf("7 - Marcar como favorito\n");
        printf("8 - Relatório: Conteúdos mais assistidos\n");
        printf("9 - Relatório: Categorias populares\n");
        printf("10 - Relatório: Utilizadores mais ativos\n");
        printf("11 - Recomendações\n");
        printf("12 - Salvar dados\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n--- Lista de Conteúdos ---\n");
                for (int i = 0; i < contentsCount; i++) {
                    printf("ID: %d | %s | %s | %d min | %d+ | %d visualizações\n",
                           contents[i].id, contents[i].titulo, contents[i].categoria,
                           contents[i].duracao, contents[i].faixa_etaria, contents[i].visualizacoes);
                }
                break;
            case 2:
                addContent();
                break;
            case 3:
                removeContent();
                break;
            case 4:
                editContent();
                break;
            case 5:
                searchContent();
                break;
            case 6:
                recordInteraction();
                break;
            case 7:
                markAsFavorite();
                break;
            case 8:
                reportMostWatched();
                break;
            case 9:
                reportPopularCategories();
                break;
            case 10:
                reportMostActiveUsers();
                break;
            case 11:
                generateRecommendations();
                break;
            case 12:
                writeContentsToCSV("contents.csv");
                writeInteractionsToCSV("interactions.csv");
                printf("Dados salvos com sucesso.\n");
                break;
            case 0:
                printf("A terminar o programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
        // Limpa o buffer de entrada
        while ((dummy = getchar()) != '\n' && dummy != EOF);
    } while (opcao != 0);
}

int main() {
    /* Inicializa a capacidade das estruturas dinâmicas */
    contentsCapacity = INITIAL_CAPACITY;
    contents = malloc(contentsCapacity * sizeof(Content));
    interactionsCapacity = INITIAL_CAPACITY;
    interactions = malloc(interactionsCapacity * sizeof(Interaction));
    
    /* Carrega dados dos ficheiros CSV */
    readContentsFromCSV("contents.csv");
    readInteractionsFromCSV("interactions.csv");

    menu();
    
    /* Ao terminar, guarda os dados e liberta a memória */
    writeContentsToCSV("contents.csv");
    writeInteractionsToCSV("interactions.csv");
    
    free(contents);
    free(interactions);
    
    return 0;
}