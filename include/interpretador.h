#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "Diretorio.h"
#include "superbloco.h"
#include "bitMapInode.h"
#include "Inode.h"
#include "bloco.h"

int iniciarInterpretador(char *entrada, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[], BlocoDados *disco);
int DiretorioCaminho(char *caminho,iNode tabelaInodes[]);
void lerComandosArquivo(const char *caminhoArquivo, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[], BlocoDados *disco);
int BuscarInodePorNome(Diretorio *d, char *nome);

#endif