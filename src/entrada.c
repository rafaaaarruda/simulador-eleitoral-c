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