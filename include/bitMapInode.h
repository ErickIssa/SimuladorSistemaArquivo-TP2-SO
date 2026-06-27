#ifndef BITMAP_INODE_H
#define BITMAP_INODE_H

#define NUM_INODES 256

#include "Inode.h"

typedef struct{
    int bitmap[NUM_INODES];
} bitmapInode;

void inicializarBitmapInodes(bitmapInode *bitmap);
int idInodeValido(int idInode);
int ocuparBitMap(bitmapInode *bitmap, int idInode);
int desocuparBitMap(bitmapInode *bitmap, int idInode);
int buscarInodeLivre(bitmapInode *bitmap);

#endif