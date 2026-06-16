#ifndef INODE_H
#define INODE_H

#define NUM_BLOCOS 15
#define BLOCO_INVALIDO -1

#include <time.h>

typedef struct{
    int idInode;
    int emUso;
    int tamanhoArquivo;
    int blocosOcupados;

    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;

    int blocos[NUM_BLOCOS];
} iNode;

void inicializarInode(iNode *inode, int id);
void preencherInode(iNode *inode);
void liberarInode(iNode *inode);
int adicionarBloco(iNode *inode, int enderecoBloco);
void incrementarTamanhoArquivo(iNode *inode, int bytesEscritos);


#endif