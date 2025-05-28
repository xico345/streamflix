#ifndef DATA_H
#define DATA_H

#include "content.h"
#include "interactions.h"

/* Funções para manipular dados de conteúdos */
void readContentsFromCSV(const char *filename);
void writeContentsToCSV(const char *filename);

/* Funções para manipular dados de interações */
void readInteractionsFromCSV(const char *filename);
void writeInteractionsToCSV(const char *filename);

#endif