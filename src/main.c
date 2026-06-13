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
#include <stdlib.h>
// Se o main.c estiver na mesma pasta que o Diretorio.h, use a linha abaixo.
// Caso o Diretorio.h esteja numa pasta "include", use #include "../include/Diretorio.h"
#include "../include/Diretorio.h"

int main() {
    // Declara a estrutura do diretório
    Diretorio meu_diretorio;

    printf("--- 1. Criando o Diretorio ---\n");
    // Agora a função apenas inicializa a lista encadeada
    CriarDiretorio(&meu_diretorio);
    printf("Diretorio inicializado com sucesso na memoria!\n\n");

    printf("--- 2. Inserindo Entradas ---\n");
    // Simulando a inserção de dois arquivos e um subdiretório
    InserirEntrada(&meu_diretorio, "texto.txt", 10);
    InserirEntrada(&meu_diretorio, "codigo.c", 11);
    InserirEntrada(&meu_diretorio, "pasta_fotos", 12);

    // Lista para ver se inseriu corretamente
    ListaConteudoDiretorio(&meu_diretorio);
    printf("\n");

    printf("--- 3. Renomeando uma Entrada ---\n");
    // Mudando o nome de codigo.c para main.c
    RenomearEntrada(&meu_diretorio, "codigo.c", "main.c");

    // Lista para confirmar a mudança
    ListaConteudoDiretorio(&meu_diretorio);
    printf("\n");

    printf("--- 4. Removendo uma Entrada ---\n");
    // Apagando o texto.txt
    RemoverEntrada(&meu_diretorio, "texto.txt");

    // Lista para ver o resultado final
    ListaConteudoDiretorio(&meu_diretorio);
    printf("\n");

    return 0;
}