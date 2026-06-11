#include <stdlib.h>
#include <stdio.h>
#include "../include/bloco.h"

int main(){

    Bloco bloco;
    inicializaBloco(&bloco, 10);
    imprimeBloco(&bloco);

    return 0;
}