#ifndef CONTENT_H
#define CONTENT_H

#define MAX_TITULO 100
#define MAX_CATEGORIA 50

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char categoria[MAX_CATEGORIA];
    int duracao;           // Em minutos
    int faixa_etaria;
    int visualizacoes;
} Content;

/* Declaração de variáveis globais para conteúdos */
extern Content *contents;
extern int contentsCount;
extern int contentsCapacity;

/* Funções de gestão de conteúdos */
void addContent();
void removeContent();
void editContent();
void searchContent();
int findContentIndexById(int id);

#endif