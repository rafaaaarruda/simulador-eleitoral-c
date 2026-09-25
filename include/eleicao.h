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

typedef struct {
    Candidato candidatos[TOTAL_CANDIDATOS];
    int votos_nulos;
    int votos_brancos;
    float percentual_nulos;
    float percentual_brancos;
} Eleicao;

void cadastrar_candidatos(Eleicao *eleicao);
void realizar_primeiro_turno(Eleicao *eleicao);
int calcular_total_votos(const Eleicao *eleicao);
void calcular_percentuais(Eleicao *eleicao);

#endif
