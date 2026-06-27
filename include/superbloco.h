#ifndef SUPERBLOCO_H
#define SUPERBLOCO_H

typedef struct {
    char assinatura[8];

    int tamanho_particao;
    int tamanho_bloco;

    int total_blocos;
    int blocos_livres;

    int total_inodes;
    int inodes_livres;

} Superbloco;

void inicializaSuperBloco(Superbloco * sb, int tamParticao, int tamBloco);
#endif