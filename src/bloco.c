#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bloco.h"


void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco){
    bloco->usado = BLOCO_LIVRE;
    bloco->bytesUtilizados = 0;

    bloco->dados = (char*) malloc(sizeof(char) * tamanhoBloco);

    if(bloco->dados == NULL){
        printf("ERRO ALOCACAO BLOCO\n");
        return;
    }else{
        for(int i = 0; i < tamanhoBloco; i++){
            bloco->dados[i] = '|';
        }
    }
    
    return;
}

void insereBlocoDados(BlocoDados *bloco, char *dado){

    //como vai ser dividido?

    strcpy(bloco->dados,dado);
    bloco->bytesUtilizados = strlen(dado);

    bloco->usado = BLOCO_USADO;

    return;
}

void imprimeBlocoDados(BlocoDados *bloco) {
    if (bloco == NULL) {
        printf("Erro: Ponteiro de bloco invalido.\n");
        return;
    }

    printf("--- Informacoes do BlocoDados ---\n");

    if (bloco->usado == BLOCO_USADO) {
        printf("Status: USADO\n");
    } else {
        printf("Status: LIVRE\n");
    }

    printf("Bytes utilizados: %d\n", bloco->bytesUtilizados);

    if (bloco->dados != NULL) {
        printf("Conteudo: %s\n", bloco->dados);
    } else {
        printf("Conteudo: Nao alocado.\n");
    }

    printf("----------------------------\n");
}