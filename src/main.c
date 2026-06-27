// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "../include/bloco.h"
// #include "../include/leituraArquivo.h"

// int main(){

//     BlocoDados bloco;
//     inicializaBlocoDados(&bloco, 4096);
//     imprimeBlocoDados(&bloco);
//     ler_arquivos("data.txt");
//     listarDocumentos();

//     insereBlocoDados(&bloco, retornaDocumento(3));
//     imprimeBlocoDados(&bloco);

    //return 0;
//}
#include <stdio.h>

#include "../include/Inode.h"
#include "../include/Diretorio.h"
#include "../include/bitMapInode.h"
#include "../include/superbloco.h"
#include "../include/interpretador.h"
#include "../include/disco.h"

#define MAX_INODES 50

int main()
{
    Superbloco sb;
    iNode raiz;
    inicializarInodeRaiz (&raiz, 0);

    printf("Sistema iniciado!\n");
int tamParticao = 0;
    do{
        printf("Digite o tamanho total da particao etre 5000 a 10000 caracteres: ");
        scanf("%d",&tamParticao);
    }while(tamParticao < 5000 || tamParticao > 10000);

    int tamBloco = 1;
    do{
        printf("Digite o tamanho do bloco (menor igual a %d escolhido): ", tamParticao);
        scanf("%d",&tamBloco);
    }while(tamBloco > tamParticao || tamBloco <= 0);

    inicializaSuperBloco(&sb, tamParticao, tamBloco);

    //Cria o disco
    Disco disco;
    inicializaDisco(&disco, &sb, &raiz);

    printf("Particao criada com sucesso! UHUL\n");


    printf("Os comandos para o sistema de arquivos sao: ");
    printf("0 - Terminal\n1 - Arquivo\n");

    int op = 0;
    do{
        printf("0 - Terminal\n1 - Arquivo\n");
        scanf("%d",&op);
    }while(op != 0 || op != 1);

    if (op ==0 ){
        char entrada [100]; 
        while (1){
            printf("[simulador@aseta]: ");
            fgets(entrada, 100, stdin);
            if(iniciarInterpretador(entrada,&sb,&(disco.bitmapInode),*disco.inodes) == 0){
                break;
            }
        }
    }else if(op == 1){
        printf("ELAO");
    }
    return 0;
}
