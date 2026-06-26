#include "../include/disco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_INODES 256
 
int inicializaDisco(Disco * disco, Superbloco * superBloco, iNode * root){

    if(superBloco == NULL){
        return INFORMACOES_AUSENTES;
    }
    if(!InformacoesSaoValidas(superBloco)){
        return INFORMACOES_INVALIDAS;
    }
    
    disco->tamanho_bloco = superBloco->tamanho_bloco;
    disco->total_blocos = superBloco->total_blocos;

    disco->bitmap = (int*)malloc(sizeof(int)*superBloco->total_blocos);
    disco->blocos = (BlocoDados **)malloc(sizeof(BlocoDados)*disco->total_blocos);
    
    if(disco->bitmap == NULL){
        return ERRO_MEMORIA;
    }else{
        for(int i = 0; i < disco->total_blocos; i++){
            disco->bitmap[i] = 0;
            inicializaBlocoDados(disco->blocos[i],disco->tamanho_bloco);
        }
    }

    
    disco->inodes = (iNode **)malloc(sizeof(iNode)*N_INODES);
    disco->inodes[0] = root;

    return SUCESSO;
}

int escreveArquivo(Disco * disco, char * texto, int id_inode){

    int pos = 0;
    for(int i = 0; i< disco->total_blocos; i++){

        if(disco->bitmap[i] == 1){
            continue;
        }
            
        disco->bitmap[i] = 1;
        adicionarBloco(&disco->inodes[id_inode], i);

        int n = strlen(texto) - pos;
        int acabou = 0;
        if(n >= disco->tamanho_bloco){

            n = disco->tamanho_bloco - 1;
            
        }else{
            acabou = 1;
        }
        

        char textoBloco[disco->tamanho_bloco];
        strncpy(textoBloco, texto + pos, n);
        textoBloco[n] = '\0';
        insereBlocoDados(&disco->blocos[i],textoBloco);
        if(acabou){
            return 1;
            break;
        }
        pos += disco->tamanho_bloco -1;
        

    }
    return 0;
}

int InformacoesSaoValidas(Superbloco * Superbloco){
    return (Superbloco->tamanho_bloco > 0)&&(Superbloco->total_blocos>0);
}