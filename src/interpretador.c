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

int iniciarInterpretador(char *entrada, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]) {
    char *args[MAX_ARGS];
    int argc = 0;

    // se a string for vazia, apenas retorna para continuar a execução
    if (strlen(entrada) == 0) return 1;

    // quebra a string
    args[argc] = strtok(entrada, " "); 
    while (args[argc] != NULL && argc < MAX_ARGS - 1) {
        argc++;
        args[argc] = strtok(NULL, " ");
    }

    if (argc == 0 || args[0] == NULL) return 1;

    char *comando = args[0];

    if (strcmp(comando, "exit") == 0 || strcmp(comando, "quit") == 0) {
        printf("saindo do simulador\n");
        return 0; 
    } 
    
    else if (strcmp(comando, "init") == 0) {
        if (argc >= 3) {
            int tam_particao = atoi(args[1]);
            int tam_bloco = atoi(args[2]);
            
            inicializaSuperBloco(sb, tam_particao, tam_bloco);
            printf("particao inicializada:\n- tam Particao: %d\n- tam bloco: %d\n- inodes totais: %d\n", 
                   sb->tamanho_particao, sb->tamanho_bloco, sb->total_inodes);
        } else {
            printf("erro. uso: init <tamanho_particao> <tamanho_bloco>\n");
        }
    } 
    
    else if (strcmp(comando, "mkdir") == 0 || strcmp(comando, "touch") == 0) {
        if (argc >= 2) {
            char *caminho = args[1];
            int inodePai = DiretorioCaminho(caminho, tabelaInodes);

            if (inodePai == -1) {
                printf("Erro: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL)
                nome = caminho;
            else
                nome++;

            int novoInode = alocarInode(bitmap, tabelaInodes);

            if (novoInode == -1) {
                printf("Erro: sem inodes livres!\n");
                return 1;
            }
            
            if (strcmp(comando, "mkdir") == 0)
                preencherInode(&tabelaInodes[novoInode], DIRETORIO);
            else
                preencherInode(&tabelaInodes[novoInode], ARQUIVO);
            
            InserirEntrada(tabelaInodes[inodePai].dir, nome, novoInode);
            printf("'%s' criado com inode [%d]\n", nome, novoInode);

        } else {
            printf("Erro. Uso: %s <caminho>\n", comando);
        }
    }
    
    else if (strcmp(comando, "ls") == 0) {
        if (argc == 1) {
            ListaConteudoDiretorio(tabelaInodes[0].dir);
        } else {
            int inode = DiretorioCaminho(args[1], tabelaInodes);
            if (inode == -1) {
                printf("Diretorio nao encontrado!\n");
                return 1;
            }
            ListaConteudoDiretorio(tabelaInodes[inode].dir);
        }
    }
    
    else if (strcmp(comando, "rename") == 0) {
        if (argc >= 3) {
            char *caminho = args[1];
            int inodePai = DiretorioCaminho(caminho, tabelaInodes);

            if (inodePai == -1) {
                printf("Erro: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL)
                nome = caminho;
            else
                nome++;
            
            RenomearEntrada(tabelaInodes[inodePai].dir, nome, args[2]);
            printf("comando de renomear executado.\n");

        } else {
            printf("erro. uso: rename <nome_atual> <novo_nome>\n");
        }
    }

    else if (strcmp(comando, "rm") == 0) {
        if (argc >= 2) {
            char *caminho = args[1];
            int inodePai = DiretorioCaminho(caminho, tabelaInodes);

            if (inodePai == -1) {
                printf("Erro: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL)
                nome = caminho;
            else
                nome++;

            RemoverEntrada(tabelaInodes[inodePai].dir, nome);

        } else {
            printf("Erro. Uso: rm <caminho>\n");
        }
    }
    else {
        printf("comando nao reconhecido: '%s'\n", comando);
    }

    return 1; // Retorna 1 para indicar que deve continuar processando o próximo comando
}

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