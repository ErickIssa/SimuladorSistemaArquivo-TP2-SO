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
} Bloco;

void inicializaBloco(Bloco *bloco, int tamanhoBloco);
void imprimeBloco(Bloco *bloco);

#endif