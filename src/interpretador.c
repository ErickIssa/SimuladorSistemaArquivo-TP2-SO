#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/interpretador.h"
#include "../include/Diretorio.h"
#include "../include/superbloco.h"
#include "../include/bitMapInode.h"
#include "../include/Inode.h"
#include "../include/leituraArquivo.h"
#include "../include/bloco.h"

#define MAX_INPUT 256
#define MAX_ARGS 10

//criar um diretorio raiz Inicial automaticamente
//Para isso criar um Inode passando TipoInode=DIRETORIO, que contenha o Inode 0
//PreecherInode cria um diretorio já
//venho do main ja sabendo que tenho um diretorio raiz(IDnode 0)

void iniciarInterpretador(Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]) {
    char entrada[MAX_INPUT];
    char *args[MAX_ARGS];

    printf("--- Simulador de Sistema de Arquivos (TP2) ---\n");
    
    while (1) {
        printf("\n[simulador@os2026 ~]$ ");

        if (fgets(entrada, MAX_INPUT, stdin) == NULL) break;
        entrada[strcspn(entrada, "\n")] = 0;
        if (strlen(entrada) == 0) continue;

        int argc = 0;
        args[argc] = strtok(entrada, " "); 
        while (args[argc] != NULL && argc < MAX_ARGS - 1) {
            argc++;
            args[argc] = strtok(NULL, " ");
        }

        char *comando = args[0];

        if (strcmp(comando, "exit") == 0 || strcmp(comando, "quit") == 0) {
            printf("saindo do simulador\n");
            break;
        } 
        
        else if (strcmp(comando, "init") == 0) {
            if (argc >= 3) {
                int tam_particao = atoi(args[1]);
                int tam_bloco = atoi(args[2]);
                
                inicializaSuperBloco(sb, tam_particao, tam_bloco);
                printf("partiao inicializada:\n- tam Particao: %d\n- tam bloco: %d\n- inodes totais: %d\n", 
                       sb->tamanho_particao, sb->tamanho_bloco, sb->total_inodes);
            } else {
                printf("erro. uso: init <tamanho_particao> <tamanho_bloco>\n");
            }
        } 
        
        else if (strcmp(comando, "mkdir") == 0 || strcmp(comando, "touch") == 0) {

            if (argc >= 2) {

                char *caminho = args[1];

                int inodePai = DiretorioCaminho(caminho,tabelaInodes);

                if (inodePai == -1) {
                    printf("Erro: caminho invalido!\n");
                    continue;
                }

                char *nome = strrchr(caminho, '/');

                if (nome == NULL)
                    nome = caminho;
                else
                    nome++;

                int novoInode = alocarInode(bitmap, tabelaInodes);

                if (novoInode == -1) {
                    printf("Erro: sem inodes livres!\n");
                    continue;
                }
                //primeiro cria na tabela
                if (strcmp(comando, "mkdir") == 0)
                    preencherInode(&tabelaInodes[novoInode], DIRETORIO);

                else
                    preencherInode(&tabelaInodes[novoInode], ARQUIVO);
                //depois adiciona no diretorio
                InserirEntrada( tabelaInodes[inodePai].dir, nome,novoInode);

                printf("'%s' criado com inode [%d]\n",nome,novoInode);

            } else {
                printf("Erro. Uso: %s <caminho>\n", comando);
            }
        }
        
        else if (strcmp(comando, "ls") == 0) {

            if (argc == 1) {
                ListaConteudoDiretorio(tabelaInodes[0].dir);
            } else {

                int inode = DiretorioCaminho(args[1],tabelaInodes);

                if (inode == -1) {
                    printf("Diretorio nao encontrado!\n");
                    continue;
                }

                ListaConteudoDiretorio(tabelaInodes[inode].dir);
            }
        }
        
        else if (strcmp(comando, "rename") == 0) {
            if (argc >= 3) {
                char *caminho = args[1];
                int inodePai = DiretorioCaminho(caminho,tabelaInodes);

                if (inodePai == -1) {
                    printf("Erro: caminho invalido!\n");
                    continue;
                }

                char *nome = strrchr(caminho, '/');
                if (nome == NULL)
                    nome = caminho;
                else
                    nome++;
                //printf("args[1]: %s\n",args[1]);
                //printf("args[2]: %s\n",args[2]);
                RenomearEntrada(tabelaInodes[inodePai].dir, nome, args[2]);
                printf("comando de renomear executado.\n");

            } else {
                printf("erro. uso: rename <nome_atual> <novo_nome>\n");
            }
        }

        else if (strcmp(comando, "rm") == 0) {

            if (argc >= 2) {

                char *caminho = args[1];

                int inodePai = DiretorioCaminho(caminho,tabelaInodes);

                if (inodePai == -1) {
                    printf("Erro: caminho invalido!\n");
                    continue;
                }

                char *nome = strrchr(caminho, '/');

                if (nome == NULL)
                    nome = caminho;
                else
                    nome++;

                RemoverEntrada( tabelaInodes[inodePai].dir,nome);

            } else {
                printf("Erro. Uso: rm <caminho>\n");
            }
        }

/*        else if (strcmp(comando, "import") == 0) {
            if (argc >= 2) {
                ler_arquivos(args[1]);
                imprimirDocumentos();
            } else {
                printf("erro. uso: import <arquivo_de_texto.txt>\n");
            }
        }*/

        else {
            printf("comando nao reconhecido: '%s'\n", comando);
        }
    }
}
//pecorre todo o caminho passado quebrando os / ate achar o IDInode do ultimo diretorio onde o arquivo esta
int DiretorioCaminho(char *caminho, iNode tabelaInodes[])
{
    char copia[100];
    strcpy(copia,caminho);

    char *ultimo = strrchr(copia,'/');

    // sem / → criar direto na raiz
    if(ultimo==NULL)
        return 0;

    *ultimo='\0';

    char *token=strtok(copia,"/");
    int inodeAtual=0;

    while(token!=NULL)
    {
        iNode *inode=&tabelaInodes[inodeAtual];

        if(inode->tipo!=DIRETORIO)
            return -1;

        EntradaDiretorio *atual= inode->dir->DFrente->pProx;

        while(atual!=NULL)
        {
            if(strcmp(atual->arq.Nome,token)==0)
            {
                inodeAtual=
                    atual->arq.id_Inode;

                break;
            }

            atual=atual->pProx;
        }

        if(atual==NULL)
            return -1;

        token=strtok(NULL,"/");
    }

    return inodeAtual;
}