#include <stdlib.h>
#include <stdio.h>
#include "../include/bloco.h"
#include "../include/leituraArquivo.h"

int main(){

    Bloco bloco;
    inicializaBloco(&bloco, 10);
    imprimeBloco(&bloco);
    ler_arquivos("data.txt");
    imprimirDocumentos();
    
    return 0;
}