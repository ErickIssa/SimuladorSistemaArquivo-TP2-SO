#ifndef DISCO_H
#define DISCO_H


#include "superbloco.h"

#define SUCESSO 100
#define ESPACO_INDISPONIVEL 101
#define INFORMACOES_AUSENTES 102
#define INFORMACOES_INVALIDAS 103
#define FALHA_AO_CRIAR_ARQUIVO 104
#define INDICE_FORA_DO_INTERVALO 105
#define FALHA_AO_ABRIR_ARQUIVO 106
#define ESPACO_INSUFICIENTE 107
#define ERRO_MEMORIA 108


typedef struct disco
{
    int * bitmap;
    int tamanho_bloco;
    int total_blocos;

}Disco;


int inicializaDisco(Disco * disco, Superbloco * superBloco);
int escreveEmBloco(Disco * disco, int index, char * dados);
int InformacoesSaoValidas(Superbloco * Superbloco);



#endif