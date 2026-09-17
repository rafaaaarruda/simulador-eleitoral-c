#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void ler_nome(const char *mensagem, char *nome, int tamanho) {
    while (1) {
        printf("%s", mensagem);

        if (fgets(nome, tamanho, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        nome[strcspn(nome, "\n")] = '\0';

        int valido = 1;
        int tem_letra = 0;

        for (int i = 0; nome[i] != '\0'; i++) {
            unsigned char caractere = (unsigned char)nome[i];

            if (isalpha(caractere) || caractere >= 128) {
                tem_letra = 1;
                continue;
            }

            if (caractere == ' ' || caractere == '-' || caractere == '\'') {
                continue;
            }

            valido = 0;
            break;
        }

        if (!valido || !tem_letra) {
            printf(
                "Nome inválido. Use apenas letras, espaços, hífen ou apóstrofo.\n"
            );
            continue;
        }

        return;
    }
}

static int ano_bissexto(int ano) {
    return (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0);
}

static int dias_no_mes(int mes, int ano) {
    int dias[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (mes == 2 && ano_bissexto(ano)) {
        return 29;
    }

    return dias[mes - 1];
}

void ler_data(const char *mensagem, int *dia, int *mes, int *ano) {
    char buffer[100];
    int dia_lido;
    int mes_lido;
    int ano_lido;

    while (1) {
        printf("%s", mensagem);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) != 10 ||
            buffer[2] != '/' ||
            buffer[5] != '/') {
            printf("Data inválida. Use o formato dd/mm/aaaa.\n");
            continue;
        }

        int formato_valido = 1;

        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) {
                continue;
            }

            if (!isdigit((unsigned char)buffer[i])) {
                formato_valido = 0;
                break;
            }
        }

        if (!formato_valido) {
            printf("Data inválida. Use o formato dd/mm/aaaa.\n");
            continue;
        }

        dia_lido =
            (buffer[0] - '0') * 10 +
            (buffer[1] - '0');

        mes_lido =
            (buffer[3] - '0') * 10 +
            (buffer[4] - '0');

        ano_lido =
            (buffer[6] - '0') * 1000 +
            (buffer[7] - '0') * 100 +
            (buffer[8] - '0') * 10 +
            (buffer[9] - '0');

        if (ano_lido < 1 || mes_lido < 1 || mes_lido > 12) {
            printf("Data inválida. Digite uma data existente.\n");
            continue;
        }

        if (dia_lido < 1 || dia_lido > dias_no_mes(mes_lido, ano_lido)) {
            printf("Data inválida. Digite uma data existente.\n");
            continue;
        }

        *dia = dia_lido;
        *mes = mes_lido;
        *ano = ano_lido;

        return;
    }
}