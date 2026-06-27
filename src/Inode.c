#include "Inode.h"
#include <stdlib.h>
#include <string.h>


void inicializarInodeRaiz(iNode *inode, int id) {
    inicializarInode(inode, id);

    inode->emUso = 1;
    inode->tipo = DIRETORIO;

    time_t instanteAtual = time(NULL);
    inode->dataCriacao = instanteAtual;
    inode->dataModificacao = instanteAtual;
    inode->dataAcesso = instanteAtual;

    inode->dir = malloc(sizeof(Diretorio));
    if (inode->dir != NULL) {
        CriarDiretorio(inode->dir);
    }
}

void inicializarInode(iNode *inode, int id) {
    inode->idInode = id;
    inode->emUso = 0;
    inode->tamanhoArquivo = 0;
    inode->blocosOcupados = 0;
    inode->tipo = INDEFINIDO;

    inode->dir = NULL;

    inode->dataCriacao = 0;
    inode->dataModificacao = 0;
    inode->dataAcesso = 0;

    for (int i = 0; i < NUM_BLOCOS_DIRETOS; i++) {
        inode->blocosDiretos[i] = BLOCO_INVALIDO;
    }

    inode->blocoIndireto = BLOCO_INVALIDO;

}

void preencherInode(iNode *inode, TipoInode tipopassado) {
    inode->emUso = 1;
    inode->tipo=tipopassado;
    time_t instanteAtual = time(NULL);

    inode->dataCriacao = instanteAtual;
    inode->dataModificacao = instanteAtual;
    inode->dataAcesso = instanteAtual;

    inode->tamanhoArquivo = 0; //cada caractere é um 1 byte
    inode->blocosOcupados = 0;

    for (int i = 0; i < NUM_BLOCOS_DIRETOS; i++) {
        inode->blocosDiretos[i] = BLOCO_INVALIDO;
    }

    inode->blocoIndireto = BLOCO_INVALIDO;

    if(tipopassado==DIRETORIO)
    {
        inode->dir=
            malloc(sizeof(Diretorio));

        CriarDiretorio(inode->dir);
    }
    else
    {
        inode->dir=NULL;
    }

}

void liberarInode(iNode *inode) {
    inode->emUso = 0;
    inode->tamanhoArquivo = 0;
    inode->blocosOcupados = 0;

    inode->dataCriacao = 0;
    inode->dataModificacao = 0;
    inode->dataAcesso = 0;

    inode->tipo = INDEFINIDO;

    if (inode->dir != NULL) {
        free(inode->dir);
        inode->dir = NULL;
    }

    for (int i = 0; i < NUM_BLOCOS_DIRETOS; i++) {
        inode->blocosDiretos[i] = BLOCO_INVALIDO;
    }

    inode->blocoIndireto = BLOCO_INVALIDO;

}

int adicionarBloco(iNode *inode, int enderecoBloco) {
    if (inode->emUso == 0) {
        return 0;
    }

    if (inode->blocosOcupados >= NUM_BLOCOS_DIRETOS) {
        return 0;
    }

    inode->blocosDiretos[inode->blocosOcupados] = enderecoBloco;
    inode->blocosOcupados++;

    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);

    return 1;
}

int removerBloco(iNode *inode) {
    if (inode == NULL || inode->emUso == 0) {
        return 0;
    }

    if (inode->blocosOcupados == 0) {
        return 0;
    }

    inode->blocosOcupados--;
    inode->blocosDiretos[inode->blocosOcupados] = BLOCO_INVALIDO; 

    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);

    return 1;
}

void alterarTamanhoArquivo(iNode *inode, int bytesAlterados) {
    if (inode == NULL || inode->emUso == 0) {
        return;
    }

    inode->tamanhoArquivo += bytesAlterados;
    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);
}

