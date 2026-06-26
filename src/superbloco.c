#include "../include/superbloco.h"

void inicializaSuperBloco(Superbloco * sb, int tamParticao, int tamBloco){
    sb->tamanho_particao = tamParticao;
    sb->tamanho_bloco = tamBloco;

    sb->total_blocos = tamParticao / tamBloco;
    sb->blocos_livres = sb->total_blocos;

    //Definir  o numero de I-nodes
    sb->total_inodes = 100;
    sb->inodes_livres = sb->total_inodes;


    sb->inode_raiz = 0;
}