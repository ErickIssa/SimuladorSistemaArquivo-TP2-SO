#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/bloco.h"
#include "../include/leituraArquivo.h"

int main(){

    BlocoDados bloco;
    inicializaBlocoDados(&bloco, 10);
    imprimeBlocoDados(&bloco);
    ler_arquivos("data.txt");
    imprimirDocumentos();

    insereBlocoDados(&bloco, documentos[1].conteudo);
    imprimeBlocoDados(&bloco);

    return 0;
}