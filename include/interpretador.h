#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "Diretorio.h"
#include "superbloco.h"
#include "bitMapInode.h"
#include "Inode.h"
#include "bloco.h"
#include "disco.h"

int iniciarInterpretador(char *entrada, Superbloco *sb, Disco * disco);
int DiretorioCaminho(char *caminho,iNode **tabelaInodes);
void lerComandosArquivo(const char *caminhoArquivo, Superbloco *sb, Disco * disco);
int BuscarInodePorNome(Diretorio *d, char *nome);
int BuscarInodePorCaminho(char *caminho, int inodeAtual, iNode **tabelaInodes);

#endif