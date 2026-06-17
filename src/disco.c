#include "../include/disco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int inicializaDisco(Disco * disco, Superbloco * superBloco){

    if(superBloco == NULL){
        return INFORMACOES_AUSENTES;
    }
    if(!InformacoesSaoValidas(superBloco)){
        return INFORMACOES_INVALIDAS;
    }

    disco->bitmap = (int*)malloc(sizeof(int)*superBloco->total_blocos);
    if(disco->bitmap == NULL){
        return ERRO_MEMORIA;
    }

    disco->tamanho_bloco = superBloco->tamanho_bloco;
    disco->total_blocos = superBloco->total_blocos;

    FILE * arquivo;
    arquivo = fopen("./data/arquivoDisco.txt", "w");

    if (arquivo == NULL) {
        return FALHA_AO_CRIAR_ARQUIVO;
    }

    for(int i = 0; i< disco->total_blocos; i++){
        for(int j = 0; j < disco->tamanho_bloco;j++){
            fprintf(arquivo, "_");
        }
        fprintf(arquivo,"\n");
        disco->bitmap[i] = 0;
    }
    fclose(arquivo);
    return SUCESSO;
}

int escreveEmBloco(Disco * disco, int index, char * dados){

    if(index >= disco->total_blocos){
        return INDICE_FORA_DO_INTERVALO;
    }

    int nBlocosNecessarios = (strlen(dados) + disco->tamanho_bloco - 1) / disco->tamanho_bloco;
    

    if(index + nBlocosNecessarios > disco->total_blocos){
        return ESPACO_INSUFICIENTE;
    }

    for(int i = index; i< index+nBlocosNecessarios; i++){
        if(disco->bitmap[i] == 1){
            return ESPACO_INDISPONIVEL;
        }
    }
    for(int i = index; i< index+nBlocosNecessarios; i++){
        disco->bitmap[i] = 1;
    }

    FILE * arquivo = fopen("./data/arquivoDisco.txt", "r+");
    if (arquivo == NULL) {
        return FALHA_AO_ABRIR_ARQUIVO;
    }

    long posicao = index * (disco->tamanho_bloco + 1);
    fseek(arquivo, posicao, SEEK_SET);

    int cont = 0;
    for(size_t i = 0; i<strlen(dados); i++){
        if(dados[i] == '\n'){

            fprintf(arquivo,"#");

        }else{

            fprintf(arquivo,"%c", dados[i]);

        }
        
        cont++;
        if(cont == disco->tamanho_bloco){
            fseek(arquivo, 1, SEEK_CUR);
            cont = 0;
        }
    }
    fclose(arquivo);
    return SUCESSO;
}


int InformacoesSaoValidas(Superbloco * Superbloco){
    return (Superbloco->tamanho_bloco > 0)&&(Superbloco->total_blocos>0);
}
