#ifndef BLOCO_H
#define BLOCO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/leituraArquivo.h"

enum usado {
  BLOCO_LIVRE = 0,
  BLOCO_USADO = 1,
};

typedef struct {

    //interessante por um tamanhoBloco aqui, mas em um SO o bloco nao sabe seu tamanho
    int usado;
    int bytesUtilizados;
    char *dados;
} BlocoDados;

void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco);
void imprimeBlocoDados(BlocoDados *bloco);
void insereBlocoDados(BlocoDados *bloco, char *dado);
char *toStringBlocoDados(BlocoDados *bloco, char separador);

#endif