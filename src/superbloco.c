#include "../include/superbloco.h"

void inicializaSuperBloco(Superbloco * sb, int tamParticao, int tamBloco){
    sb->tamanho_particao = tamParticao;
    sb->tamanho_bloco = tamBloco;

    sb->total_blocos = tamParticao / tamBloco;
    sb->blocos_livres = sb->total_blocos;

    //Definir  o numero de I-nodes
    sb->total_inodes = 100;
    sb->inodes_livres = sb->total_inodes;

    //Definir como vai ser as localizacoes 
    sb->inicio_bitmap_blocos = 1;
    sb->inicio_bitmap_inodes = 2;
    sb->inicio_tabela_inodes = 4;
    sb->inicio_blocos_dados = 3;

    sb->inode_raiz = 0;
}