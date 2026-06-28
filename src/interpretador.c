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
void lerComandosArquivo(const char *caminhoArquivo, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[], BlocoDados *disco) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de comandos: %s\n", caminhoArquivo);
        return;
    }

    int num_comandos = 0;
    
    if (fscanf(arquivo, "%d", &num_comandos) != 1) {
        printf("erro ao ler a quantidade de comandos\n");
        fclose(arquivo);
        return;
    }

    // limpa buffer
    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF);

    char linha[256];
    printf("--- Processando %d comandos do arquivo '%s' ---\n", num_comandos, caminhoArquivo);

    for (int i = 0; i < num_comandos; i++) {
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            printf("[Aviso] Fim de arquivo alcancado antes de ler todos os %d comandos.\n", num_comandos);
            break;
        }

        // remove a quebra de linha do final
        linha[strcspn(linha, "\r\n")] = 0;

        // pula linhas vazias que podem ter ficado no meio do arquivo de texto
        if (strlen(linha) == 0) {
            i--; // decrementa o 'i' para não contar essa linha vazia como um comando lido
            continue;
        }

        printf("\n[Lote] %s\n", linha); // modo verboso(comentar caso queira apenas o resultado final)

        // envia a string formatada para o interpretador principal
        if (iniciarInterpretador(linha, sb, bitmap, tabelaInodes, disco) == 0) {
            // se o interpretador retornar 0 (encontrou um exit/quit), paramos a leitura do arquivo
            break; 
        }
    }

    printf("\n--- Fim da leitura do arquivo ---\n");
    fclose(arquivo);
}
int BuscarInodePorNome(Diretorio *d, char *nome) {
    if (d == NULL || d->DFrente == d->DTras) { // Verifica se está vazio
        return -1;
    }
    
    EntradaDiretorio *atual = d->DFrente->pProx;
    while (atual != NULL) {
        if (strcmp(atual->arq.Nome, nome) == 0) {
            return atual->arq.id_Inode;
        }
        atual = atual->pProx;
    }
    return -1; // Não encontrou
}

int iniciarInterpretador(char *entrada, Superbloco *sb, bitmapInode *bitmap, iNode tabelaInodes[], BlocoDados *disco) {
    char *args[MAX_ARGS];
    int argc = 0;

    // se a string for vazia, apenas retorna para continuar a execução
    if (strlen(entrada) == 0) return 1;

    // quebra a string
    args[argc] = strtok(entrada, " \n\r"); 
    while (args[argc] != NULL && argc < MAX_ARGS - 1) {
        argc++;
        args[argc] = strtok(NULL, " \n\r");
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
                printf("erro: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL) nome = caminho; else nome++;

            int idExistente = BuscarInodePorNome(tabelaInodes[inodePai].dir, nome);

            if (idExistente != -1) {
                if (strcmp(comando, "mkdir") == 0) {
                    printf("mkdir: nao foi possivel criar '%s': O arquivo/diretorio ja existe\n", nome);
                } else {
                    // touch em algo que já existe -> atualiza timestamp
                    tabelaInodes[idExistente].dataModificacao = time(NULL);
                    tabelaInodes[idExistente].dataAcesso = time(NULL);
                    printf("touch: datas de '%s' atualizadas.\n", nome);
                }
            } else {
                int novoInode = buscarInodeLivre(bitmap);
                if (novoInode != -1) {
                    ocuparBitMap(bitmap, novoInode);
                }
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
            }
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
                printf("erro: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL) nome = caminho; else nome++;
            
            // checa se o arquivo/pasta original existe
            if (BuscarInodePorNome(tabelaInodes[inodePai].dir, nome) == -1) {
                printf("rename: nao foi possivel renomear '%s': n existe\n", nome);
            } else {
                RenomearEntrada(tabelaInodes[inodePai].dir, nome, args[2]);
                printf("'%s' renomeado para '%s'.\n", nome, args[2]);
            }
        } else {
            printf("erro. uso: rename <nome_atual> <novo_nome>\n");
        }
    }

    else if (strcmp(comando, "rm") == 0) {
        if (argc >= 2) {
            int flag_r = 0;
            char *caminho;

            //verfica o uso de -r
            if (strcmp(args[1], "-r") == 0) {
                if (argc < 3) {
                    printf("Erro. Uso: rm -r <caminho>\n");
                    return 1; // continua o interpretador
                }
                flag_r = 1;
                caminho = args[2];
            } else {
                caminho = args[1];
            }

            int inodePai = DiretorioCaminho(caminho, tabelaInodes);
            if (inodePai == -1) {
                printf("rm: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL) nome = caminho; else nome++;
            int idAlvo = BuscarInodePorNome(tabelaInodes[inodePai].dir, nome);

            if (idAlvo == -1) {
                printf("rm: nao foi possivel remover '%s': Arquivo ou diretorio inexistente\n", nome);
            } 
            // bloqueia a remoção de diretórios sem a flag -r
            else if (tabelaInodes[idAlvo].tipo == DIRETORIO && flag_r == 0) {
                printf("rm: nao foi possivel remover '%s': E um diretorio (use -r)\n", nome);
            } 
            else {
                RemoverEntrada(tabelaInodes[inodePai].dir, nome);
                printf("'%s' removido com sucesso.\n", nome);
                desocuparBitMap(bitmap, idAlvo);
                liberarInode(&tabelaInodes[idAlvo]);
            }
        } else {
            printf("Erro. Uso: rm [-r] <caminho>\n");
        }
    }
    else if (strcmp(comando, "cat") == 0) {
        if (argc >= 2) {
            char *caminho = args[1];
            int inodePai = DiretorioCaminho(caminho, tabelaInodes);

            if (inodePai == -1) {
                printf("cat: caminho invalido!\n");
                return 1;
            }

            char *nome = strrchr(caminho, '/');
            if (nome == NULL) nome = caminho; else nome++;

            int idAlvo = BuscarInodePorNome(tabelaInodes[inodePai].dir, nome);

            if (idAlvo == -1) {
                printf("cat: %s: Arquivo ou diretorio inexistente\n", nome);
            } else if (tabelaInodes[idAlvo].tipo == DIRETORIO) {
                printf("cat: %s: E um diretorio!\n", nome);
            } else {
                // espaço pra leitura de blocos
                printf("[Aviso] Lendo arquivo inode [%d]. Back-end de blocos pendente.\n", idAlvo);
            }
        } else {
            printf("Erro. Uso: cat <caminho>\n");
        }
    }else
    if(strcmp(comando, "escreva")==0){
        //char *texto = selecionaRetornaDocumento();
        //Terminar depois ...
    }
    else {
        printf("comando nao reconhecido: '%s'\n", comando);
    }

    return 1; 
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