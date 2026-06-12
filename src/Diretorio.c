// Diretorio.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Diretorio.h"

void CriarDiretorio(Diretorio *d, char nome[64]){
    strcpy(d->NomeDiretorio, nome);
    d->DFrente = (EntradaDiretorio*)malloc(sizeof(EntradaDiretorio));
    d->tam = 0;
    d->DTras = d->DFrente;
    d->DFrente->pProx = NULL;
}

int DiretorioVazio(Diretorio *d){
    return (d->DFrente == d->DTras);
}

void InserirEntrada(Diretorio *d, char nome[64], int inode){
    EntradaDiretorio *nova = (EntradaDiretorio*) malloc(sizeof(EntradaDiretorio));

    strcpy(nova->arq.Nome, nome);
    nova->arq.id_Inode = inode;
    nova->pProx = NULL;

    d->DTras->pProx = nova;
    d->DTras = nova;
    d->tam++;
}

void RenomearEntrada(Diretorio *d, char nomeAtual[64], char novoNome[64]){
    EntradaDiretorio* atual = d->DFrente->pProx;

    while (atual != NULL) {
        if (strcmp(atual->arq.Nome, nomeAtual) == 0) {
            strcpy(atual->arq.Nome, novoNome);
            return;
        }
        atual = atual->pProx;
    }
}

void RemoverEntrada(Diretorio *d, char nome[64]){
    if (DiretorioVazio(d)) {
        printf("O diretorio esta vazio!\n");
        return;
    }

    EntradaDiretorio* anterior = d->DFrente;
    EntradaDiretorio* atual = d->DFrente->pProx;

    while (atual != NULL) {
        if (strcmp(atual->arq.Nome, nome) == 0) {
            anterior->pProx = atual->pProx;

            if (atual == d->DTras) {
                d->DTras = anterior;
            }

            free(atual);
            d->tam--;
            printf("Entrada apagada com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->pProx;
    }
    printf("A entrada não foi encontrada!\n");
}

void ListaConteudoDiretorio(Diretorio *d){
    if(DiretorioVazio(d)){
        printf("Diretorio vazio!!!\n");
        return;
    }

    EntradaDiretorio* aux = d->DFrente->pProx;
    do{
        printf("Nome: %s | ID_Inode: %d\n", aux->arq.Nome, aux->arq.id_Inode);
        aux = aux->pProx;
    } while(aux != NULL);
}