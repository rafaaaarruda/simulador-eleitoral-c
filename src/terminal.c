#include <stdio.h>
#include <stdlib.h>

#include "terminal.h"

void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[3J\033[H");
    fflush(stdout);
#endif
}

void pausar(void) {
    int caractere;

    printf("Pressione Enter para continuar...");
    fflush(stdout);

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}
