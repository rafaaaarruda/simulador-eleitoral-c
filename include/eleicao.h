#ifndef ELEICAO_H
#define ELEICAO_H

#define TOTAL_CANDIDATOS 4
#define TAMANHO_NOME 50

typedef struct {
    int numero;
    char nome[TAMANHO_NOME];
    int votos;
    float percentual;
} Candidato;

#endif