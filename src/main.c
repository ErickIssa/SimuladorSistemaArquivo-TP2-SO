#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "../include/bloco.h"
//#include "../include/leituraArquivo.h"

//int main(){

    // BlocoDados bloco;
    // inicializaBloco(&bloco, 10);
    // imprimeBloco(&bloco);
    // ler_arquivos("data.txt");
    // imprimirDocumentos();

    // insereBloco(&bloco, documentos[1].conteudo);
    // imprimeBloco(&bloco);

    //return 0;
//}
#include <stdio.h>

#include "../include/Inode.h"
#include "../include/Diretorio.h"
#include "../include/bitMapInode.h"
#include "../include/superbloco.h"
#include "../include/interpretador.h"

#define MAX_INODES 50

int main()
{
    Superbloco sb;
    bitmapInode bitmap;

    iNode tabelaInodes[MAX_INODES];

    // Inicializa tabela de i-nodes
    for(int i=0;i<MAX_INODES;i++)
    {
        inicializarInode(
            &tabelaInodes[i],
            i
        );
    }

    // Inicializa bitmap
    inicializarBitmapInodes(
        &bitmap
    );



    // Cria diretório raiz
    marcarInodeOcupado(
        &bitmap,
        0
    );

    preencherInode(
        &tabelaInodes[0],
        DIRETORIO
    );

    printf("Sistema iniciado!\n");
    printf("Diretorio raiz criado no inode 0\n");

    // Inicia terminal
    iniciarInterpretador(
        &sb,
        &bitmap,
        tabelaInodes
    );

    return 0;
}