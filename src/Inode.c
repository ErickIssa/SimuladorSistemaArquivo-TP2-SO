#include "Inode.h"
#include <stdlib.h>
#include <string.h>

void inicializarInode(iNode *inode, int id) {
    inode->idInode = id;
    inode->emUso = 0;
    inode->tamanhoArquivo = 0;
    inode->blocosOcupados = 0;
    inode->tipo = 3;
    inode->dir = NULL;
    inode->dataCriacao = 0;
    inode->dataModificacao = 0;
    inode->dataAcesso = 0;

    for (int i = 0; i < NUM_BLOCOS; i++) {
        inode->blocos[i] = BLOCO_INVALIDO;
    }

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

    for (int i = 0; i < NUM_BLOCOS; i++) {
        inode->blocos[i] = BLOCO_INVALIDO;
    }

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

    for (int i = 0; i < NUM_BLOCOS; i++) {
        inode->blocos[i] = BLOCO_INVALIDO;
    }

}

int adicionarBloco(iNode *inode, int enderecoBloco) {
    if (inode->emUso == 0) {
        return 0;
    }

    if (inode->blocosOcupados >= NUM_BLOCOS) {
        return 0;
    }

    inode->blocos[inode->blocosOcupados] = enderecoBloco;
    inode->blocosOcupados++;

    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);

    //uma funcao de bloco que indique que o bloco esta ocupado

    return 1;
}

void incrementarTamanhoArquivo(iNode *inode, int bytesEscritos) {
    if (inode == NULL || inode->emUso == 0) {
        return;
    }

    inode->tamanhoArquivo += bytesEscritos;
    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);
}

