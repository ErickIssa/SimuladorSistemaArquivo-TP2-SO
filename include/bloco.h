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

void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco);
void imprimeBlocoDados(BlocoDados *bloco);
void insereBlocoDados(BlocoDados *bloco, char *dado);

#endif