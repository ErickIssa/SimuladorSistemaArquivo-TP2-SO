#include "../include/superbloco.h"
#include <stdio.h>


void inicializaSuperBloco(Superbloco * sb, int tamParticao, int tamBloco){
    sb->tamanho_particao = tamParticao;
    sb->tamanho_bloco = tamBloco;

    sb->total_blocos = tamParticao / tamBloco;
    sb->blocos_livres = sb->total_blocos;

    //Definir  o numero de I-nodes
    sb->total_inodes = 256;
    sb->inodes_livres = sb->total_inodes;

}

void imprimirSuperBloco(const Superbloco *sb) {
    if (sb == NULL) {
        printf("Erro: Superbloco inexistente.\n");
        return;
    }

    printf("\n========== SUPERBLOCO ==========\n");
    printf("Assinatura        : %s\n", sb->assinatura);
    printf("Tamanho Particao  : %d bytes\n", sb->tamanho_particao);
    printf("Tamanho Bloco     : %d bytes\n", sb->tamanho_bloco);
    printf("Total de Blocos   : %d\n", sb->total_blocos);
    printf("Blocos Livres     : %d\n", sb->blocos_livres);
    printf("Total de Inodes   : %d\n", sb->total_inodes);
    printf("Inodes Livres     : %d\n", sb->inodes_livres);
    printf("================================\n");
}