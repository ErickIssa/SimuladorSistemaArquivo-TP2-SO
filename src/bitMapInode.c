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

int ocuparBitMap(bitmapInode* bitmap, int idInode) {
    if (!idInodeValido(idInode)) {
        return -1;
    }

    bitmap->bitmap[idInode] = 1;
    return 0;
}

int desocuparBitMap(bitmapInode *bitmap, int idInode) {
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

void imprimirBitmapInodes(bitmapInode *bitmap) {
    if (bitmap == NULL) {
        printf("Bitmap de inodes inexistente.\n");
        return;
    }

    printf("Bitmap de Inodes:\n");

    for (int i = 0; i < 10; i++) {
        printf("[%2d] = %d\n", i, bitmap->bitmap[i]);
    }
}

