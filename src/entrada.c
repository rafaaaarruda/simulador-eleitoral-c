#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "entrada.h"

static int ler_linha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        return -1;
    }

    size_t comprimento = strlen(buffer);

    if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
        buffer[comprimento - 1] = '\0';
        return 1;
    }

    int caractere = getchar();

    if (caractere == '\n' || caractere == EOF) {
        return 1;
    }

    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }

    return 0;
}

int ler_inteiro(const char *mensagem) {
    char buffer[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        int status = ler_linha(buffer, sizeof(buffer));

        if (status == -1) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        if (status == 0) {
            printf("Entrada muito longa. Digite um número inteiro válido.\n");
            continue;
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

        int status = ler_linha(nome, tamanho);

        if (status == -1) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        if (status == 0) {
            printf(
                "Nome muito longo. Use no máximo %d caracteres.\n",
                tamanho - 1
            );
            continue;
        }

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

        int status = ler_linha(buffer, sizeof(buffer));

        if (status == -1) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        if (status == 0) {
            printf("Data inválida. Use o formato dd/mm/aaaa.\n");
            continue;
        }

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
