#include <stdio.h>
#include <stdlib.h>

#include "terminal.h"

void limpar_tela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar(void) {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione Enter para continuar...");
        getchar();
        getchar();
    #endif
}