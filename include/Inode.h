#ifndef INODE_H
#define INODE_H

#define NUM_BLOCOS_DIRETOS 10
#define NUM_BLOCOS_INDIRETOS 1
#define BLOCO_INVALIDO -1

#include <time.h>
#include "Diretorio.h"

typedef enum{
    ARQUIVO,
    DIRETORIO,
    INDEFINIDO = -1
} TipoInode;

typedef struct iNode{
    int idInode;
    int emUso;
    int tamanhoArquivo;
    int blocosOcupados;

    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;

    TipoInode tipo;
    Diretorio* dir; //usado somente caso for um diretorio

    int blocosDiretos[NUM_BLOCOS_DIRETOS];
    int blocoIndireto;

} iNode;

void inicializarInode(iNode *inode, int id);
void inicializarInodeRaiz(iNode *inode, int id);
void preencherInode(iNode *inode,TipoInode tipopassado);
void liberarInode(iNode *inode);
int adicionarBloco(iNode *inode, int enderecoBloco);
int removerBloco(iNode *inode);
void alterarTamanhoArquivo(iNode *inode, int bytesAlterados);

#endif