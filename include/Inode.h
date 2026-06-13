#ifndef INODE_H
#define INODE_H

#define NUM_BLOCOS 15

#include <time.h>

typedef struct{
    int idInode;
    int emUso;
    int tamanhoArquivo;
    int blocosOcupados;

    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;

    //blocoDedados blocos[NUM_BLOCOS];
} iNode;

void inicializarInode(iNode *inode, int id);
void preencherInode(iNode *inode);
void liberarInode(iNode *inode);
int adicionarBloco(iNode *inode, int enderecoBloco);


#endif