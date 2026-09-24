#include "eleicao.h"

int calcular_total_votos(const Eleicao *eleicao) {
    int total = eleicao->votos_nulos + eleicao->votos_brancos;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}