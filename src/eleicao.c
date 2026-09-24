#include <stdio.h>

#include "entrada.h"
#include "eleicao.h"

void cadastrar_candidatos(Eleicao *eleicao) {
    int numero_valido = 0;
    char mensagem[100];

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        snprintf(
            mensagem,
            sizeof(mensagem),
            "Digite o número do %d° candidato(a): ",
            i + 1
        );

        eleicao->candidatos[i].numero = ler_inteiro(mensagem);

        do {
            if (numero_valido == 1) {
                eleicao->candidatos[i].numero = ler_inteiro(
                    "Número do candidato(a) inválido. Digite novamente: "
                );
            }

            for (int j = 0; j < TOTAL_CANDIDATOS; j++) {
                if (i != j) {
                    if (eleicao->candidatos[i].numero == eleicao->candidatos[j].numero) {
                        numero_valido = 1;
                        break;
                    } else {
                        numero_valido = 0;
                    }
                }
            }
        } while (numero_valido == 1);

        snprintf(
            mensagem,
            sizeof(mensagem),
            "Digite o nome do %d° candidato(a): ",
            i + 1
        );

        ler_nome(
            mensagem,
            eleicao->candidatos[i].nome,
            sizeof(eleicao->candidatos[i].nome)
        );

        puts(" ");
    }
}

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