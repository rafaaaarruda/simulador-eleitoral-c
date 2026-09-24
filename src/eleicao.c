#include "eleicao.h"

int calcular_total_votos(const Eleicao *eleicao) {
    int total = eleicao->votos_nulos + eleicao->votos_brancos;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}

static int calcular_total_votos_validos(const Eleicao *eleicao) {
    int total = 0;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}

void calcular_percentuais(Eleicao *eleicao) {
    int total_votos = calcular_total_votos(eleicao);
    int total_votos_validos = calcular_total_votos_validos(eleicao);

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        if (total_votos_validos > 0) {
            eleicao->candidatos[i].percentual =
                (eleicao->candidatos[i].votos * 100.0f) / total_votos_validos;
        } else {
            eleicao->candidatos[i].percentual = 0.0f;
        }
    }

    if (total_votos > 0) {
        eleicao->percentual_nulos =
            (eleicao->votos_nulos * 100.0f) / total_votos;

        eleicao->percentual_brancos =
            (eleicao->votos_brancos * 100.0f) / total_votos;
    } else {
        eleicao->percentual_nulos = 0.0f;
        eleicao->percentual_brancos = 0.0f;
    }
}