#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bloco.h"


void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco){

    bloco->bytesUtilizados = 0;

    bloco->dados = (char*) malloc(sizeof(char) * (tamanhoBloco+1));

    if(bloco->dados == NULL){
        printf("ERRO ALOCACAO BLOCO\n");
        return;
    }else{
        for(int i = 0; i < tamanhoBloco; i++){
            bloco->dados[i] = '|';
        }
    }
    
    bloco->dados[tamanhoBloco] = '\0'; 
    return;
}

void insereBlocoDados(BlocoDados *bloco, char *dado){


    strcpy(bloco->dados,dado);  
    bloco->bytesUtilizados = strlen(dado);


    return;
}

void imprimeBlocoDados(BlocoDados *bloco) {
    if (bloco == NULL) {
        printf("Erro: Ponteiro de bloco invalido.\n");
        return;
    }

    printf("--- Informacoes do BlocoDados ---\n");


    printf("Bytes utilizados: %d\n", bloco->bytesUtilizados);

    if (bloco->dados != NULL) {
        printf("Conteudo: %s\n", bloco->dados);
    } else {
        printf("Conteudo: Nao alocado.\n");
    }

    printf("----------------------------\n");
}