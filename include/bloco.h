#ifndef BLOCO_H
#define BLOCO_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int bytesUtilizados;
    char *dados;
} BlocoDados;

void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco);
void imprimeBlocoDados(BlocoDados *bloco);
void insereBlocoDados(BlocoDados *bloco, char *dado);

#endif