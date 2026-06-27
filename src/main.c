#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/bloco.h"
#include "../include/leituraArquivo.h"

int main(){

    BlocoDados bloco;
    inicializaBlocoDados(&bloco, 4096);
    imprimeBlocoDados(&bloco);
    ler_arquivos("data.txt");
    listarDocumentos();

    insereBlocoDados(&bloco, retornaDocumento(1));
    imprimeBlocoDados(&bloco);

    return 0;
}
