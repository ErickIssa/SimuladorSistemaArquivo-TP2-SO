
#ifndef DIRETORIO_H
#define DIRETORIO_H


typedef struct {
    char Nome[64];
    int id_Inode;
} Celula;

typedef struct EntradaDiretorio {
    Celula arq;
    struct EntradaDiretorio* pProx;
} EntradaDiretorio;

typedef struct Diretorio {
    EntradaDiretorio* DFrente;
    EntradaDiretorio* DTras;
    int tam;
} Diretorio;

void CriarDiretorio(Diretorio *d);
int DiretorioVazio(Diretorio *d);
void InserirEntrada(Diretorio *d, char nome[64], int inode);
void RenomearEntrada(Diretorio *d, char nomeAtual[64], char novoNome[64]);
void RemoverEntrada(Diretorio *d, char nome[64]);
void ListaConteudoDiretorio(Diretorio *d);

#endif