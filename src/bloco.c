#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bloco.h"


void inicializaBlocoDados(BlocoDados *bloco, int tamanhoBloco){
    bloco->usado = BLOCO_LIVRE;
    bloco->bytesUtilizados = 0;

    bloco->dados = (char*) malloc(sizeof(char) * (tamanhoBloco + 1)); // + 1 pra por o \0

    if(bloco->dados == NULL){
        printf("ERRO ALOCACAO BLOCO\n");
        return;
    }else{
        for(int i = 0; i < tamanhoBloco; i++){
            bloco->dados[i] = '|';
        }
        bloco->dados[tamanhoBloco] = '\0';
    }
    
    return;
}

void insereBlocoDados(BlocoDados *bloco, char *dado){

    //como vai ser dividido?

    strcpy(bloco->dados,dado);
    bloco->bytesUtilizados = strlen(dado) + 1; //caractere \0

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
        printf("Bloco esta ocupado.\n");
    } else {
        printf("Bloco esta livre.\n");
    }

    printf("Bytes utilizados: %d\n", bloco->bytesUtilizados);

    printf("Conteudo: ");
    imprimeStringDebug(bloco->dados);

    printf("----------------------------\n");
}

char *toStringBlocoDados(BlocoDados *bloco, char separador) {

    if (bloco == NULL){
        return NULL;
        printf("ERRO BLOCO NULL no toString\n");
    }

    //esse snprintf calcula calcula o tamanho quando é passado com esse null ai, usado so pro malloc
    int tamanho = snprintf(NULL,0,"%d%c%d%c%s",bloco->usado,separador,
    bloco->bytesUtilizados,separador,bloco->dados); 

    char *resultado = malloc((tamanho + 1) * sizeof(char));

    if (resultado == NULL){
        printf("ERRO ALOCACAO STRING BLOCO\n");
        return NULL;
    }
    //com a variavel resultado, é escrita a string formatada
    sprintf(resultado,"%d%c%d%c%s",bloco->usado,separador,bloco->bytesUtilizados,separador,bloco->dados);
    imprimeStringDebug(resultado);

    return resultado;
}