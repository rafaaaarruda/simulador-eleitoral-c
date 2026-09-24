#include "eleicao.h"

int calcular_total_votos(const Eleicao *eleicao) {
    int total = eleicao->votos_nulos + eleicao->votos_brancos;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}

void calcular_percentuais(Eleicao *eleicao) {
    int total_votos = calcular_total_votos(eleicao);

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        eleicao->candidatos[i].percentual =
            (eleicao->candidatos[i].votos * 100.0f) / total_votos;
    }

    eleicao->percentual_nulos =
        (eleicao->votos_nulos * 100.0f) / total_votos;

    eleicao->percentual_brancos =
        (eleicao->votos_brancos * 100.0f) / total_votos;
}