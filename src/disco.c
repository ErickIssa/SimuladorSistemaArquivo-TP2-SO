#include "../include/disco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_INODES 256
 
int inicializaDisco(Disco *disco, Superbloco *superBloco) {

    if (superBloco == NULL)
        return INFORMACOES_AUSENTES;

    if (!InformacoesSaoValidas(superBloco))
        return INFORMACOES_INVALIDAS;

    inicializarBitmapInodes(&disco->bitmapInode);

    // Bitmap
    disco->bitmap = malloc(sizeof(int) * superBloco->total_blocos);
    if (disco->bitmap == NULL)
        return ERRO_MEMORIA;

    // Vetor de ponteiros para blocos
    disco->blocos = malloc(sizeof(BlocoDados *) * superBloco->total_blocos);
    if (disco->blocos == NULL)
        return ERRO_MEMORIA;

    for (int i = 0; i < superBloco->total_blocos; i++) {

        disco->bitmap[i] = 0;

        disco->blocos[i] = malloc(sizeof(BlocoDados));
        if (disco->blocos[i] == NULL)
            return ERRO_MEMORIA;

        inicializaBlocoDados(disco->blocos[i], superBloco->tamanho_bloco);
    }

    // Vetor de ponteiros para inodes
    disco->inodes = malloc(sizeof(iNode *) * N_INODES);
    if (disco->inodes == NULL)
        return ERRO_MEMORIA;

    disco->inodes[0] = malloc(sizeof(iNode));
    if (disco->inodes[0] == NULL)
        return ERRO_MEMORIA;

    // Inicializa o inode raiz
    inicializarInodeRaiz(disco->inodes[0], 0);
    ocuparBitMap(&disco->bitmapInode, 0);

    // Demais inodes
    for (int i = 1; i < N_INODES; i++) {

        disco->inodes[i] = malloc(sizeof(iNode));
        if (disco->inodes[i] == NULL)
            return ERRO_MEMORIA;

        inicializarInode(disco->inodes[i], i);
    }

    return SUCESSO;
}

int escreveArquivo(Disco * disco, Superbloco * superBloco, char * texto, int id_inode){

    liberarInode(disco->inodes[id_inode]);
    disco->bitmapInode.bitmap[id_inode] = 1;
    preencherInode(disco->inodes[id_inode], ARQUIVO);
    alterarTamanhoArquivo(disco->inodes[id_inode], strlen(texto));
    superBloco->inodes_livres--;


    int nBlocos = strlen(texto)/superBloco->tamanho_bloco;
    if(strlen(texto)%superBloco->tamanho_bloco != 0){
        nBlocos++;
    }
    if(nBlocos>superBloco->blocos_livres){
        return ARQUIVO_NAO_CABE_NO_DISCO;
    }else{
        superBloco->blocos_livres -= nBlocos;
    }

    int pos = 0;
    for(int i = 0; i< superBloco->total_blocos; i++){

        if(disco->bitmap[i] == 1){
            continue;
        }
            
        disco->bitmap[i] = 1;
        adicionarBloco(disco->inodes[id_inode], i);

        int n = strlen(texto) - pos;
        int acabou = 0;
        if(n >= superBloco->tamanho_bloco){

            n = superBloco->tamanho_bloco - 1;
            
        }else{
            acabou = 1;
        }
        

        char textoBloco[superBloco->tamanho_bloco];
        strncpy(textoBloco, texto + pos, n);
        textoBloco[n] = '\0';
        insereBlocoDados(disco->blocos[i],textoBloco);
        if(acabou){
            return SUCESSO;
            break;
        }
        pos += superBloco->tamanho_bloco -1;
        

    }
    return FALHOU;
}

int InformacoesSaoValidas(Superbloco * Superbloco){
    return (Superbloco->tamanho_bloco > 0)&&(Superbloco->total_blocos>0);
}

int apagaArquivo(Disco * disco, Superbloco * superBloco, int id_inode){

    superBloco->inodes_livres++;
    superBloco->blocos_livres += disco->inodes[id_inode]->blocosOcupados;

    for(int i = 0; i< disco->inodes[id_inode]->blocosOcupados; i++){
        int index = disco->inodes[id_inode]->blocosDiretos[i];
        disco->bitmap[index] = 0;
    }

    disco->bitmapInode.bitmap[id_inode] = 0;

    return SUCESSO;

}

char * retornaArquivo(Disco * disco, Superbloco * superBloco, int id_inode){



    char * texto;
    texto = (char *)malloc(sizeof(char)*disco->inodes[id_inode]->blocosOcupados* superBloco->tamanho_bloco);

    for(int i = 0; i< disco->inodes[id_inode]->blocosOcupados; i++){

        strcat(texto,retornaBloco(disco,disco->inodes[id_inode]->blocosDiretos[i]));

    }

    return texto;

}

char * retornaBloco(Disco * disco, int id_bloco){

    return disco->blocos[id_bloco]->dados;

}
int escreveBlocoEnderecoIndireto(Disco* disco, Superbloco superBloco, char * texto, int * id){
    if(superBloco.blocos_livres <= 0){
        return DISCO_LOTADO;
    }
    if((int)strlen(texto)> superBloco.tamanho_bloco){
        return TEXTO_NAO_CABE_NO_BLOCO;
    }
    for(int i = 0; i< superBloco.total_blocos;i++){
        if(disco->bitmap[i] == 1){
            continue;
        }
        disco->bitmap[i] = 1;
        insereBlocoDados(disco->blocos[i],texto);
        *id = i;
        return SUCESSO;
    }
    return FALHOU;
}