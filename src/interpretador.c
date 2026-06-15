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


void iniciarTerminal(Diretorio *dir_atual, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[]) {
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
                char *nome = args[1];
                
                int id_inode = alocarInode(bitmap, tabelaInodes);
                
                if (id_inode != -1) {
                    InserirEntrada(dir_atual, nome, id_inode);
                    printf("entrada '%s' associada ao Inode [%d].\n", nome, id_inode);
                    
                    if(sb->inodes_livres > 0) sb->inodes_livres--; 
                } else {
                    printf("erro: sem inodes livres disponiveis no bitmap!\n");
                }
            } else {
                printf("erro. uso: %s <nome>\n", comando);
            }
        } 
        
        else if (strcmp(comando, "ls") == 0) {
            ListaConteudoDiretorio(dir_atual);
        }
        
        else if (strcmp(comando, "rename") == 0) {
            if (argc >= 3) {
                RenomearEntrada(dir_atual, args[1], args[2]);
                printf("comando de renomear executado.\n");
            } else {
                printf("erro. uso: rename <nome_atual> <novo_nome>\n");
            }
        }

        else if (strcmp(comando, "rm") == 0) {
            if (argc >= 2) {
                RemoverEntrada(dir_atual, args[1]);

            } else {
                printf("erro. uso: rm <nome>\n");
            }
        }

        else if (strcmp(comando, "import") == 0) {
            if (argc >= 2) {
                ler_arquivos(args[1]);
                imprimirDocumentos();
            } else {
                printf("erro. uso: import <arquivo_de_texto.txt>\n");
            }
        }

        else {
            printf("comando nao reconhecido: '%s'\n", comando);
        }
    }
}