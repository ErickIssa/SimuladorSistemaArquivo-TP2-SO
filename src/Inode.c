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

void inicializarInode(iNode* inode, int id) {

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

void preencherInode(iNode *inode, TipoInode tipopassado, int tamanhoArquivo,int qtdBlocos, int* endBlocosDiretos, int endIndireto) {

    inode->emUso = 1;
    inode->tipo=tipopassado;
    time_t instanteAtual = time(NULL);

    inode->dataCriacao = instanteAtual;
    inode->dataModificacao = instanteAtual;
    inode->dataAcesso = instanteAtual;

    inode->tamanhoArquivo = tamanhoArquivo; //cada caractere é um 1 byte

    inode->blocosOcupados = qtdBlocos;

    int qtdDiretos;

    if (qtdBlocos < NUM_BLOCOS_DIRETOS) {
        qtdDiretos = qtdBlocos;
    } else {
        qtdDiretos = NUM_BLOCOS_DIRETOS;
    }

    for (int i = 0; i < NUM_BLOCOS_DIRETOS; i++) {
        if (i < qtdDiretos)
            inode->blocosDiretos[i] = endBlocosDiretos[i];
        else
            inode->blocosDiretos[i] = BLOCO_INVALIDO;
    }

    inode->blocoIndireto = BLOCO_INVALIDO;

    if (qtdBlocos > NUM_BLOCOS_DIRETOS)
        inode->blocoIndireto = endIndireto;

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
    if (inode == NULL)
        return;

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

void incrementarTamanhoArquivo(iNode *inode, int bytesEscritos) {
    if (inode == NULL || inode->emUso == 0) {
        return;
    }

    inode->tamanhoArquivo += bytesEscritos;
    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);
}

//verificar se tem blocos diretos livres, senao, usar bloco indireto (responsabilidade do disco??)
void atualizarInode(iNode *inode, int novoTamanhoArquivo, int novaQtdBlocos, int *novosBlocosDiretos, int novoBlocoIndireto){
    if (inode == NULL || inode->emUso == 0) {
        return;
    }

    inode->tamanhoArquivo = novoTamanhoArquivo;
    inode->blocosOcupados = novaQtdBlocos;

    for (int i = 0; i < NUM_BLOCOS_DIRETOS; i++) {

        if (i < novaQtdBlocos && i < NUM_BLOCOS_DIRETOS)
            inode->blocosDiretos[i] = novosBlocosDiretos[i];
        else
            inode->blocosDiretos[i] = BLOCO_INVALIDO;
    }

    if (novaQtdBlocos > NUM_BLOCOS_DIRETOS)
        inode->blocoIndireto = novoBlocoIndireto;
    else
        inode->blocoIndireto = BLOCO_INVALIDO;

    inode->dataModificacao = time(NULL);
    inode->dataAcesso = time(NULL);
}

void acessarInode(iNode *inode){
    inode->dataAcesso = time(NULL);
}
