#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "entrada.h"

int ler_inteiro(const char *mensagem) {
    char buffer[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        errno = 0;
        valor = strtol(buffer, &fim, 10);

        if (fim == buffer) {
            printf("Entrada inválida. Digite um número inteiro.\n");
            continue;
        }

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (*fim != '\0') {
            printf("Entrada inválida. Digite apenas números inteiros.\n");
            continue;
        }

        if (errno == ERANGE || valor < INT_MIN || valor > INT_MAX) {
            printf("Número fora do intervalo permitido.\n");
            continue;
        }

        return (int)valor;
    }
}

void ler_data(const char *mensagem, int *dia, int *mes, int *ano) {
    char buffer[100];
    char extra;
    int dia_lido, mes_lido, ano_lido;

    while (1) {
        printf("%s", mensagem);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        if (sscanf(
                buffer,
                "%d/%d/%d %c",
                &dia_lido,
                &mes_lido,
                &ano_lido,
                &extra
            ) != 3) {
            printf("Data inválida. Use o formato dd/mm/aaaa.\n");
            continue;
        }

        if (dia_lido < 1 || dia_lido > 31 ||
            mes_lido < 1 || mes_lido > 12 ||
            ano_lido < 1) {
            printf("Data inválida. Digite novamente.\n");
            continue;
        }

        *dia = dia_lido;
        *mes = mes_lido;
        *ano = ano_lido;

        return;
    }
}