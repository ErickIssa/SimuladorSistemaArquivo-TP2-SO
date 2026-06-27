#ifndef DISCO_H
#define DISCO_H


#include "superbloco.h"
#include "bloco.h"
#include "Inode.h"
#include "bitMapInode.h"

#define SUCESSO 100
#define FALHOU 101
#define INFORMACOES_AUSENTES 102
#define INFORMACOES_INVALIDAS 103
#define ERRO_MEMORIA 104
#define ARQUIVO_NAO_CABE_NO_DISCO 105
#define DISCO_LOTADO 106
#define TEXTO_NAO_CABE_NO_BLOCO 107


typedef struct disco
{
    int * bitmap;
    bitmapInode bitmapInode;
    BlocoDados ** blocos;
    iNode ** inodes;

}Disco;


int inicializaDisco(Disco * disco, Superbloco * superBloco, iNode * root);
int InformacoesSaoValidas(Superbloco * Superbloco);
int escreveArquivo(Disco * disco, Superbloco * superBloco, char * texto, int id_inode);
int apagaArquivo(Disco * disco, Superbloco * superBloco, int id_inode);
char * retornaArquivo(Disco * disco, Superbloco * superBloco, int id_inode);
char * retornaBloco(Disco * disco, int id_bloco);
int escreveBlocoEnderecoIndireto(Disco* disco, Superbloco superBloco, char * texto, int * id);



#endif