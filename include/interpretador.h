#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "Diretorio.h"
#include "superbloco.h"
#include "bitMapInode.h"
#include "Inode.h"

void iniciarInterpretador(Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]);
int DiretorioCaminho(char *caminho,iNode tabelaInodes[]);

#endif