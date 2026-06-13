// Diretorio.h
#ifndef DIRETORIO_H
#define DIRETORIO_H
/* A ideia é que diretorios podem guardar diretorios, ja que os mesmos são um arquivo especial
   que ao envez de dados guardam Inodes para outros arquivos.
   Um diretorio dentro de outro diretorio( é um arquivo comum)
   mais a cima na hierarquiva teriamos um diretorio raiz(o diretorio do computador(que n pode apagar)
   e seus outros diretorios seriam tratodos como arquivos la "dentro"
   MAIS A CIMA teremos no arquivo o tipoarquivo que usaremos identificar que aquilo é um arquivo
   e usar os RevomerEntrada
*/
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

void CriarDiretorio(Diretorio *d, char nome[64]);
int DiretorioVazio(Diretorio *d);
void InserirEntrada(Diretorio *d, char nome[64], int inode);
void RenomearEntrada(Diretorio *d, char nomeAtual[64], char novoNome[64]);
void RemoverEntrada(Diretorio *d, char nome[64]);
void ListaConteudoDiretorio(Diretorio *d);

#endif