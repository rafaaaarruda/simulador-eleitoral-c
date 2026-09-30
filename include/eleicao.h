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
void realizar_segundo_turno(Eleicao *eleicao, int primeiro, int segundo);
void identificar_primeiro_segundo(const Eleicao *eleicao, int *primeiro, int *segundo);
void exibir_resultados(const Eleicao *eleicao, int num_eleitores);
int calcular_total_votos(const Eleicao *eleicao);
void calcular_percentuais(Eleicao *eleicao);

#endif
