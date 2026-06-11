#include "../include/bloco.h"

#include <stdlib.h>
#include <stdio.h>


void inicializaBloco(Bloco *bloco, int tamanhoBloco){
    bloco->usado = BLOCO_LIVRE;
    bloco->bytesUtilizados = 0;

    bloco->dados = (char*) malloc(sizeof(char) * tamanhoBloco);

    if(bloco->dados == NULL){
        printf("ERRO ALOCACAO BLOCO\n");
        return;
    }else{
        for(int i = 0; i <= tamanhoBloco; i++){
            bloco->dados[i] = '|';
        }
    }
    
    return;
}

void imprimeBloco(Bloco *bloco) {
    if (bloco == NULL) {
        printf("Erro: Ponteiro de bloco invalido.\n");
        return;
    }

    printf("--- Informacoes do Bloco ---\n");

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