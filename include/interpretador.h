#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "Diretorio.h"
#include "superbloco.h"
#include "bitMapInode.h"
#include "Inode.h"

void iniciarInterpretador(Diretorio *dir_atual, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]);

#endif