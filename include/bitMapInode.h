#ifndef BITMAP_INODE_H
#define BITMAP_INODE_H

#define NUM_INODES 128

#include "Inode.h"

typedef struct{
    int bitmap[NUM_INODES];
} bitmapInode;

void inicializarBitmapInodes(bitmapInode *bitmap);
int idInodeValido(int idInode);
int marcarInodeOcupado(bitmapInode *bitmap, int idInode);
int marcarInodeLivre(bitmapInode *bitmap, int idInode);

int buscarInodeLivre(bitmapInode *bitmap);
int alocarInode(bitmapInode *bitmap, iNode tabelaInodes[]);
int desalocarInode(bitmapInode *bitmap, iNode tabelaInodes[], int idInode);


#endif