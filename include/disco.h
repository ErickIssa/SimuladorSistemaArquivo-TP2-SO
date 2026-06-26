#ifndef DISCO_H
#define DISCO_H


#include "superbloco.h"
#include "bloco.h"
#include "Inode.h"

#define SUCESSO 100
#define INFORMACOES_AUSENTES 102
#define INFORMACOES_INVALIDAS 103
#define ERRO_MEMORIA 108


typedef struct disco
{
    int * bitmap;
    int tamanho_bloco;
    int total_blocos;
    BlocoDados ** blocos;
    iNode ** inodes;

}Disco;


int inicializaDisco(Disco * disco, Superbloco * superBloco, iNode * root);
int InformacoesSaoValidas(Superbloco * Superbloco);
int escreveArquivo(Disco * disco, char * texto, int id_inode);
int apagaArquivo(Disco * disco, int id_inode);
int adicionaInode(Disco * disco);



#endif