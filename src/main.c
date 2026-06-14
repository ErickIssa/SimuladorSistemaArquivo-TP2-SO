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

    insereBlocoDados(&bloco, documentos[0].conteudo);
    imprimeBlocoDados(&bloco);
    toStringBlocoDados(&bloco, '|');

    return 0;
}


//teste


// #include <stdio.h>
// #include <stdlib.h>

// #include "../include/bloco.h"

// int main() {

//     printf("\n===== TESTE 1 =====\n");

//     BlocoDados bloco1;
//     inicializaBlocoDados(&bloco1, 32);

//     imprimeBlocoDados(&bloco1);

//     insereBlocoDados(&bloco1, "Ola Mundo");

//     imprimeBlocoDados(&bloco1);

//     char *str1 = toStringBlocoDados(&bloco1, '|');

//     printf("toString: ");
//     imprimeStringDebug(str1);

//     free(str1);
//     free(bloco1.dados);



//     printf("\n===== TESTE 2 =====\n");

//     BlocoDados bloco2;
//     inicializaBlocoDados(&bloco2, 64);

//     insereBlocoDados(&bloco2,
//         "Linha 1\nLinha 2\nLinha 3");

//     imprimeBlocoDados(&bloco2);

//     char *str2 = toStringBlocoDados(&bloco2, ';');

//     printf("toString: ");
//     imprimeStringDebug(str2);

//     free(str2);
//     free(bloco2.dados);



//     printf("\n===== TESTE 3 =====\n");

//     BlocoDados bloco3;
//     inicializaBlocoDados(&bloco3, 16);

//     insereBlocoDados(&bloco3, "");

//     imprimeBlocoDados(&bloco3);

//     char *str3 = toStringBlocoDados(&bloco3, '#');

//     printf("toString: ");
//     imprimeStringDebug(str3);

//     free(str3);
//     free(bloco3.dados);



//     printf("\n===== TESTE 4 =====\n");

//     BlocoDados bloco4;
//     inicializaBlocoDados(&bloco4, 128);

//     insereBlocoDados(
//         &bloco4,
//         "abcdefghijklmnopqrstuvwxyz"
//     );

//     imprimeBlocoDados(&bloco4);

//     char *str4 = toStringBlocoDados(&bloco4, ',');

//     printf("toString: ");
//     imprimeStringDebug(str4);

//     free(str4);
//     free(bloco4.dados);



//     printf("\n===== TODOS OS TESTES FINALIZADOS =====\n");

//     return 0;
// }
