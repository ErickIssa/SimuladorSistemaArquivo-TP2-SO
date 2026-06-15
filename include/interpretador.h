#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

// Inclui os cabeçalhos das tuas estruturas para que o interpretador conheça os tipos de dados
#include "Diretorio.h"
#include "superbloco.h"
#include "bitMapInode.h"
#include "Inode.h"

void iniciarInterpretador(Diretorio *dir_atual, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]);

#endif