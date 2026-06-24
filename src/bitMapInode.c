#include "bitMapInode.h"
#include <stdio.h>


void inicializarBitmapInodes(bitmapInode *bitmap) {
    for (int i = 0; i < NUM_INODES; i++) {
        bitmap->bitmap[i] = 0;
    }
}

int idInodeValido(int idInode){
    return (idInode >= 0 && idInode < NUM_INODES);
}

int marcarInodeOcupado(bitmapInode* bitmap, int idInode) {
    if (!idInodeValido(idInode)) {
        return -1;
    }

    bitmap->bitmap[idInode] = 1;
    return 0;
}

int marcarInodeLivre(bitmapInode *bitmap, int idInode) {
    if (!idInodeValido(idInode)) {
        return -1;
    }

    bitmap->bitmap[idInode] = 0;
    return 0;
}

int buscarInodeLivre(bitmapInode *bitmap) {
    for (int i = 0; i < NUM_INODES; i++) {
        if (bitmap->bitmap[i] == 0) {
            return i;
        }
    }
    return -1;
}

int alocarInode(bitmapInode *bitmap, iNode tabelaInodes[]) {

    int idLivre = buscarInodeLivre(bitmap);

    if (idLivre == -1) {
        return -1;
    }

    marcarInodeOcupado(bitmap, idLivre);

    //preencherInode(&tabelaInodes[idLivre]); //id global de inodes
    tabelaInodes[idLivre].idInode = idLivre;

    return idLivre;
}

int desalocarInode(bitmapInode *bitmap, iNode tabelaInodes[], int idInode) {

    if (!idInodeValido(idInode)) {
        return -1;
    }

    if (bitmap->bitmap[idInode] == 0) {
        return -1;
    }

    marcarInodeLivre(bitmap, idInode);

    liberarInode(&tabelaInodes[idInode]);
    tabelaInodes[idInode].idInode = idInode;

    return 0;
}
