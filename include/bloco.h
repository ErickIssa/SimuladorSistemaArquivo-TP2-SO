#ifndef BLOCO_H
#define BLOCO_H

#include <stdlib.h>
#include <stdio.h>

enum usado {
  BLOCO_LIVRE = 0,
  BLOCO_USADO = 1,
};

typedef struct {
    int usado;
    int bytesUtilizados;
    char *dados;
} BlocoDados;

void inicializaBloco(BlocoDados *bloco, int tamanhoBloco);
void imprimeBloco(BlocoDados *bloco);
void insereBloco(BlocoDados *bloco, char *dado);

#endif