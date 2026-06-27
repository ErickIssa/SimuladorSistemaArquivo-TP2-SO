/* 
Grupo: Os 01
Matheus - 5909
Gabriel - 5921
Erick - 5926
Vítor - 5906
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/leituraArquivo.h"

// Vetor global que armazenará todos os documentos carregados
Documento documentos[MAX_DOCS];

// Variável global que armazena a quantidade de documentos
int num_documentos = 0;

int docs_lidos = 0;

char *letras_permitidas[] = {
    NULL
};

int ehLetraPermitida(char *palavra) {
    for (int i = 0; letras_permitidas[i] != NULL; i++) {
        if (strcmp(palavra, letras_permitidas[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void limparConteudo(char *entrada, char *saida) {
    char temporaria[10000];
    int j = 0;

    // Etapa 1: remove sinais e coloca em minúscula
    for (int i = 0; entrada[i] != '\0'; i++) {
        unsigned char c = (unsigned char) entrada[i];
        if (c == '\n' || c == '\r' || c == '\t') {
            temporaria[j++] = ' ';
        } else{
            temporaria[j++] = c;
        }
    }
    temporaria[j] = '\0';
    
    char *token = strtok(temporaria, " ");
    j = 0;
    while (token != NULL) {
        int tamanho = strlen(token);
        if ((tamanho > 0 || ehLetraPermitida(token))) {
            if (j > 0) saida[j++] = ' ';
            memcpy(&saida[j], token, tamanho);
            j += tamanho;
        }
        token = strtok(NULL, " ");
    }
    saida[j] = '\0';
}

void ler_arquivos(char *arquivo_entrada) {
    FILE *fp = fopen(arquivo_entrada, "r");

if (!fp) {
    perror("Erro ao abrir arquivo de entrada");
    printf("Tentando abrir: %s\n", arquivo_entrada);
    return;
}

    // Lê do arquivo a quantidade de documentos que deverão ser processados
    if (fscanf(fp, "%d", &num_documentos) != 1) {
        fprintf(stderr, "Erro ao ler o numero de documentos\n");
        fclose(fp);
        return;
    }

    // Lê até 'num_documentos' nomes de arquivos ou até atingir MAX_DOCS
    for (int i = 0; i < num_documentos && docs_lidos < MAX_DOCS; i++) {
        // Lê o nome do arquivo
        if (fscanf(fp, "%s", documentos[docs_lidos].nome) != 1) {
            fprintf(stderr, "Erro ao ler o nome do arquivo no indice %d\n", i);
            break;
        }

        // Atribui um ID para o documento
        documentos[docs_lidos].id = docs_lidos + 1;

        char caminho_completo[256];
        snprintf(caminho_completo, sizeof(caminho_completo), "./data/%s", documentos[docs_lidos].nome);
        FILE *doc = fopen(caminho_completo, "r");
        if (!doc) {
            perror("Erro ao abrir arquivo de texto");
            continue; // Não aumenta o numero de documentos lidos
        }

        // Move o ponteiro de leitura para o fim do arquivo para descobrir o tamanho
        fseek(doc, 0, SEEK_END);
        long tamanho = ftell(doc); // Salva o tamanho total em bytes
        fseek(doc, 0, SEEK_SET);   // Volta para o início do arquivo

        // Aloca memória para armazenar o conteúdo do arquivo + 1 byte para o '\0'
        documentos[docs_lidos].conteudo = malloc(tamanho + 1);
        if (!documentos[docs_lidos].conteudo) {
            fprintf(stderr, "Erro de alocacao de memoria para o conteudo do documento %s\n", documentos[docs_lidos].nome);
            fclose(doc);
            continue;
        }

        // Lê o conteúdo do arquivo e salva no conteudo do tad
        // "lidos" recebe quantos bytes foram efetivamente lidos
        size_t lidos = fread(documentos[docs_lidos].conteudo, 1, tamanho, doc);

        // Garante que a string esteja corretamente terminada com '\0' (fim da string)
        documentos[docs_lidos].conteudo[lidos] = '\0';

        char *limpo = malloc(tamanho + 1); // +1 para o '\0'
        if (limpo == NULL) {
            perror("Erro ao alocar memória");
            exit(1);
        }

        // printf("Conteudo antes de ser limpo:\n%s\n", documentos[docs_lidos].conteudo);

        // Limpa sinais, numeros e caracteres do conteudo
        limparConteudo(documentos[docs_lidos].conteudo, limpo);

        // Conteudo filtrado do documento é definido
        free(documentos[docs_lidos].conteudo);
        documentos[docs_lidos].conteudo = limpo;

        // printf("Documento %d: %s\n", docs_lidos + 1, documentos[docs_lidos].conteudo);

        // char *conteudo_copia = strdup(documentos[docs_lidos].conteudo);

        // free(conteudo_copia);

        fclose(doc);

        // Aumenta o contador de documentos lidos com sucesso
        docs_lidos++;
    }

    // Apenas os documentos realmente carregados
    num_documentos = docs_lidos;

    fclose(fp);
}

void imprimirDocumentos() {
    printf("\n===== DOCUMENTOS CARREGADOS =====\n");

    for (int i = 0; i < num_documentos; i++) {
        printf("\nDocumento %d\n", i + 1);
        printf("ID: %d\n", documentos[i].id);
        printf("Nome: %s\n", documentos[i].nome);

        if (documentos[i].conteudo != NULL) {
            printf("Conteudo:\n%s\n", documentos[i].conteudo);
        } else {
            printf("Conteudo: NULL\n");
        }

        printf("---------------------------------\n");
    }

    printf("Total de documentos: %d\n", num_documentos);
}

void listarDocumentos() {

    if( num_documentos == 0) {
        printf("Nenhum documento carregado.\n");
        return;
    }else{
        printf("\n===== LISTA DE DOCUMENTOS =====\n");
            for (int i = 0; i < num_documentos; i++) {
                printf("Documento %d: %s\n", documentos[i].id, documentos[i].nome);
        }
    }
    return;
}

char* retornaDocumento(int id) {
    for (int i = 0; i < num_documentos; i++) {
        if (documentos[i].id == id) {
            return documentos[i].conteudo;
        }
    }
    printf("Documento com ID %d não encontrado.\n", id);
    return NULL; // Retorna NULL se o documento não for encontrado
}

char* selecionaRetornaDocumento(){
    int id;
    printf("Digite o ID do documento que deseja acessar: ");
    scanf("%d", &id);
    return retornaDocumento(id);
}