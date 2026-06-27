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

    printf("Diretorio raiz criado no inode 0\n");

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
            scanf("%s",&entrada);
            if(iniciarInterpretador(entrada,&sb,&bitmap,tabelaInodes) == 0){
                break;
            }
        }
    }elif( op == 1){
        
    }
    return 0;
}