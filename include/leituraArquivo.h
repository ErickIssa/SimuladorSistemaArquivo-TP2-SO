/* 
Grupo: Os 01
Matheus - 5909
Gabriel - 5921
Erick - 5926
Vítor - 5906
*/
#ifndef LEITURA_ARQUIVOS_H_
#define LEITURA_ARQUIVOS_H_

#define MAX_DOCS 100

typedef struct {
    int id;
    char nome[100];       // nome do arquivo, ex: "doc1.txt"
    char *conteudo;       // texto lido (título + resumo + palavras-chave)
} Documento;

void limparConteudo(char *entrada, char *saida);
void ler_arquivos(char *arquivo_entrada);
void imprimirDocumentos();
void listarDocumentos();
char* retornaDocumento(int id);
char* selecionaRetornaDocumento();
// Acesso a  documentos e num_documentos em outros arquivos
extern Documento documentos[MAX_DOCS];
extern int num_documentos;

#endif