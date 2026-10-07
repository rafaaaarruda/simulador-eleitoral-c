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
#ifdef _WIN32
    system("pause");
#else
    printf("Pressione Enter para continuar...");
    getchar();
#endif
}