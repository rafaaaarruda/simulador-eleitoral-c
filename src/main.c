// Simulador Eleitoral em C
// Projeto acadêmico desenvolvido em 2024.2
// Versão revisada em 2026 para organização de portfólio 
// Mantém a proposta original, com correções pontuais de lógica e compatibilidade

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "entrada.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    int  opcao_menu, voto, senha = 1234, num_eleitores;
    int cont1[2] = {0, 0}, cont2[4] = {0, 0, 0, 0}, controle[4] = {0, 0, 0, 0};
    float votos[6] = {0, 0, 0, 0, 0, 0}, total_votos, total_votos_validos;
    int confirmar_voto, idade[2] = {0 , 0};
    int numero_candidato[4] = {0, 0, 0, 0};
    char nome_candidato[4][50];
    int maior_voto = 0, segundo_maior_voto = 0;
    int primeiro = 0, segundo = 0, numero_valido = 0;
    int dia[2], mes[2], ano[2];


            do {
                printf("--------------Menu--------------\n\n");
                printf("1 - Cadastrar Candidatos\n");
                printf("2 - Iniciar votação\n");
                printf("3 - Encerrar votação\n");
                printf("4 - Computar os votos\n");
                printf("5 - Sair\n\n");


                opcao_menu = ler_inteiro("Digite a opção desejada: ");

                while (opcao_menu < 1 || opcao_menu > 5) {
                    opcao_menu = ler_inteiro("Opção inválida. Digite novamente: ");
                }
                pausar();
                    limpar_tela();

                if (opcao_menu == 1){
                    if ( controle[0] == 1 ){
                        printf("Já foi feito o cadastro de candidatos.\n\n");
                    } else {
                        senha = ler_inteiro("Digite a senha: ");
                            limpar_tela();

                    while (senha != 1234){
                        senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");

                                    if ( senha == 0 ){
                                        break;
                                    }

                                    limpar_tela();
                        }

                            if (senha == 1234){

                                    controle[0] = 1;

                                    for (int i = 0; i < 4; i++){
                                            printf("Digite o número do %d° candidato(a): ", i+1);
                                                scanf("%d", &numero_candidato[i]);

                                                    do {
                                                        if (numero_valido == 1){
                                                            printf("Número do candidato(a) inválido. Digite novamente: ");
                                                                scanf("%d", &numero_candidato[i]);
                                                        }

                                                        for (int j = 0; j < 4; j++){
                                                            if ( i != j ){
                                                                if (numero_candidato[i] == numero_candidato[j]){
                                                                    numero_valido = 1;
                                                                        break;
                                                                } else {
                                                                    numero_valido = 0;
                                                                }
                                                            }
                                                        }
                                                    } while (numero_valido == 1 );

                                            fflush(stdin); // sem da erro qnd vai pedir o nome
                                                printf("Digite o nome do %d° candidato(a): ", i + 1);
                                                    fgets(nome_candidato[i], 50, stdin);
                                                        nome_candidato[i][strcspn(nome_candidato[i], "\n")] = '\0';  // remove o '\n' ao final para não ficar pulando linha


                                            puts(" ");
                                    } // fim for

                            } // fim senha

                    } // fim controle
                            pausar();
                                limpar_tela();
                } // fim if 1

                if (opcao_menu == 2){
                    if ( controle[1] == 1 ){
                        printf("Votação já foi encerrada. Compute os votos para saber o vencedor.\n\n");

                    } else if (numero_candidato[3] != 0){
                                senha = ler_inteiro("Digite a senha: ");
                                    limpar_tela();

                                while (senha != 1234){
                                    senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");

                                        if ( senha == 0 ){
                                            break;
                                        }

                                        limpar_tela();

                                    }

                            if (senha == 1234){
                                    if ( controle[3] != 1){
                                        printf("-------Qntd. de Eleitores-------\n");
                                        printf("[1] + de 200k\n");
                                        printf("[2] - de 200k\n");
                                        printf("Digite uma opção: ");
                                            scanf("%d", &num_eleitores);


                                        while ( num_eleitores != 1 && num_eleitores != 2 ){
                                            printf("Número de eleitores inválido. Digite novamente: ");
                                                scanf("%d", &num_eleitores);
                                        }

                                        pausar();
                                        limpar_tela();

                                    }
                                        do{

                                            controle [3] = 1;

                                            printf("----------Primeiro turno----------\n");
                                            printf("[1] - Voto Branco\n");
                                            printf("[100] - Sair da votação\n");
                                            printf("Digite o número do seu candidato(a) ou uma das opções acima: ");
                                                scanf("%d", &voto);

                                                while ( voto < 0 ){
                                                    printf("\nVoto inválido. Digite novamente: ");
                                                        scanf("%d", &voto);
                                                }

                                                    if (voto == 100){
                                                        printf("\nFim da votação.\n\n");


                                                    } else if (voto == 1){
                                                             printf("\nVocê está votando Branco. Para confirmar seu voto digite 1: ");
                                                                scanf("%d", &confirmar_voto);

                                                                    if (confirmar_voto == 1){
                                                                        cont1[1] += 1;
                                                                    }
                                                                            limpar_tela();

                                                    } else if ( voto == numero_candidato[0]){
                                                         printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[0]);
                                                            scanf("%d", &confirmar_voto);

                                                                if (confirmar_voto == 1){
                                                                    cont2[0] += 1;
                                                                }
                                                                        limpar_tela();

                                                    } else if ( voto == numero_candidato[1]){
                                                         printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[1]);
                                                            scanf("%d", &confirmar_voto);

                                                                if (confirmar_voto == 1){
                                                                    cont2[1] += 1;
                                                                }
                                                                        limpar_tela();

                                                    }else if ( voto == numero_candidato[2]){
                                                         printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[2]);
                                                            scanf("%d", &confirmar_voto);

                                                                if (confirmar_voto == 1){
                                                                    cont2[2] += 1;
                                                                }
                                                                        limpar_tela();

                                                    }else if ( voto == numero_candidato[3]){
                                                         printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[3]);
                                                            scanf("%d", &confirmar_voto);

                                                                if (confirmar_voto == 1){
                                                                    cont2[3] += 1;
                                                                }
                                                                        limpar_tela();

                                                    } else {
                                                         printf("\nVocê está votando Nulo. Para confirmar seu voto digite 1: ");
                                                            scanf("%d", &confirmar_voto);

                                                                if (confirmar_voto == 1){
                                                                    cont1[0] += 1;
                                                                }
                                                                        limpar_tela();

                                                    } // fim da votação

                                        } while ( voto != 100); // fim do "do" caso o numero_candidato[3] seja != 0

                            } //fim senha

                        } else {
                            printf("Ainda não foram cadastrados candidatos. \n\n");

                        } // fim do if (numero_candidato[3] != 0)

                        pausar();
                            limpar_tela();

                } // fim do if (opcao_menu == 2)

                if (opcao_menu == 3){
                    if ( controle[1] == 1 ){
                        printf("A votação já foi encerrada. Compute os votos para saber o ganhador.\n\n");
                    } else if ( cont2[0] == 0 && cont2[1] == 0 && cont2[2] == 0 && cont2[3] == 0  ){
                                printf("Ainda não foi feita a eleição.\n\n");
                            } else if (numero_candidato[3] != 0){
                                do{
                                    senha = ler_inteiro("Digite a senha: ");
                                        limpar_tela();

                                        while (senha != 1234){
                                            senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");

                                                if ( senha == 0 ){
                                                    break;
                                                }

                                            limpar_tela();
                                        }

                                        if (senha == 1234){

                                                controle[1] = 1;

                                                total_votos = cont1[0] + cont1[1] + cont2[0] + cont2[1] + cont2[2] + cont2[3];

                                                for (int i = 0; i < 4; i++){
                                                    votos[i] = ( cont2[i] * 100 ) / total_votos;
                                                }

                                                votos[4] = ( cont1[0] * 100 ) / total_votos; //votos nulos
                                                votos[5] = ( cont1[1] * 100 ) / total_votos; //votos brancos

                                                printf("Votos encerrados.\n\n");

                                        } // fim do if senha

                                } while (0); // fim do "do" caso o numero_candidato[3] seja != 0

                            } else {
                                printf("Ainda não foram cadastrados candidatos. \n\n");

                            } // fim do if (numero_candidato[3] != 0)

                                pausar();
                                    limpar_tela();

                } // fim do if (opcao_menu == 3)

                if (opcao_menu == 4 ){
                    if ( controle[2] == 1 ){
                        printf("O resultado da eleição já foi divulgado. O candidato(a) %s[%d] ganhou.\n\n", nome_candidato[primeiro], numero_candidato[primeiro]);
                    } else if ( cont2[0] == 0 && cont2[1] == 0 && cont2[2] == 0 && cont2[3] == 0  ){
                            printf("Ainda não foi feita a eleição.\n\n");
                    } else if ( votos[0] == 0 && votos[1] == 0 && votos[2] == 0 && votos[3] == 0 ){
                            printf("Ainda não foi feita a contagem de votos.\n\n");
                    } else if (numero_candidato[3] != 0){
                            do{
                                senha = ler_inteiro("Digite a senha: ");
                                    limpar_tela();

                            while (senha != 1234){
                                senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");

                                    if ( senha == 0 ){
                                        break;
                                    }

                                limpar_tela();
                            }

                                        if (senha == 1234){

                                            controle[2] = 1;

                                            if ( num_eleitores == 2 ){
                                                    for (int i = 0; i < 4; i++){
                                                    printf("Candidato(a) %s [%d] - %d votos\n", nome_candidato[i], numero_candidato[i], cont2[i]);
                                                }
                                                printf("Votos nulos - %d votos\n", cont1[0]);
                                                printf("Votos brancos - %d votos\n", cont1[1]);
                                            } else {

                                                for (int i = 0; i < 4; i++){
                                                    printf("Candidato(a) %s [%d] - %.2f%% com %d votos\n", nome_candidato[i], numero_candidato[i], votos[i], cont2[i]);
                                                }
                                                printf("Votos Nulos - %d e ocupa %.2f%% do total\n", cont1[0], votos[4]);
                                                printf("Votos Brancos - %d e ocupa %.f%% do total\n", cont1[1], votos[5]);
                                            }



                                            for (int i = 0; i < 4; i++) {
                                                    if ( cont2[i] > maior_voto ){
                                                        segundo_maior_voto = maior_voto;
                                                        maior_voto = cont2[i];
                                                        segundo = primeiro;
                                                        primeiro = i;
                                                    } else if (cont2[i] > segundo_maior_voto){
                                                        segundo_maior_voto = cont2[i];
                                                        segundo = i;
                                                    }
                                            }

                                                if ( num_eleitores == 2 ){
                                                        if ( maior_voto == segundo_maior_voto ){ //empatou 1° turno com - 200k eleitores
                                                            printf("\nNão houve vencedor. Ocorrerá desempate por meio da idade dos candidatos %s e %s. \n\n", nome_candidato[primeiro], nome_candidato[segundo]);

                                                                pausar();
                                                                    limpar_tela();

                                                            printf("Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ", nome_candidato[primeiro]);
                                                                scanf("%d/%d/%d", &dia[0], &mes[0], &ano[0]);
                                                                fflush(stdin);

                                                            printf("Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ", nome_candidato[segundo]);
                                                                scanf("%d/%d/%d", &dia[1], &mes[1], &ano[1]);
                                                                fflush(stdin);

                                                                if ( ano[0] < ano[1] ){
                                                                    printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                } else if ( ano[0] > ano[1]) {
                                                                    printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                } else { // anos diferentes -> comparar os meses
                                                                    if ( mes[0] < mes[1] ){
                                                                        printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                    } else if ( mes[0] > mes[1]) {
                                                                        printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                    } else { // meses iguais -> comparar os dias
                                                                        if ( dia[0] < dia[1] ){
                                                                            printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                        } else if ( dia[0] > dia[1]) {
                                                                            printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                        }
                                                                    }
                                                                }


                                                        } else { // nao empatou -> houve um vencedor
                                                            printf("O candidato(a) %s venceu o 1° turno.\n", nome_candidato[primeiro]);
                                                        }

                                                } else { // cidade tem mais de 200k eleitores
                                                    if ( votos[primeiro] > 50.0 ){ // if resultado da votação
                                                        printf("O candidato(a) %s venceu o 1° turno com %.2f%% dos votos válidos.\n", nome_candidato[primeiro], votos[primeiro]);
                                                    } else if ( votos[primeiro] < 50.0 ) {
                                                        printf("\nNão houve vencedor no 1° turno. Ocorrerá 2° turno entre os candidatos %s e %s. \n\n", nome_candidato[primeiro], nome_candidato[segundo]);

                                                        pausar();
                                                            limpar_tela();

                                                        // votação do segundo turno

                                                        cont2[primeiro] = 0;
                                                        cont2[segundo] = 0;
                                                        //zerar o voto dos finalistas

                                                        do{
                                                            printf("----------Segundo Turno----------\n");
                                                            printf("[1] - Voto Branco\n");
                                                            printf("[%d] - %s\n", numero_candidato[primeiro], nome_candidato[primeiro]);
                                                            printf("[%d] - %s\n", numero_candidato[segundo], nome_candidato[segundo]);
                                                            printf("[100] - Sair da votação\n");
                                                            printf("Digite o número do seu candidato(a) ou uma das opções acima: ");
                                                                scanf("%d", &voto);

                                                                while ( voto < 0 ){
                                                                        printf("\nVoto inválido. Digite novamente: ");
                                                                            scanf("%d", &voto);
                                                                }

                                                                    if (voto == 100){
                                                                            printf("\nFim da votação.\n\n");
                                                                    } else if (voto == 1) {
                                                                        printf("\nVocê está votando Branco. Para confirmar seu voto digite 1: ");
                                                                            scanf("%d", &confirmar_voto);

                                                                        if (confirmar_voto == 1){
                                                                            cont1[1] += 1;
                                                                        }
                                                                                limpar_tela();

                                                                    } else if ( voto == numero_candidato[primeiro] ){
                                                                        printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[primeiro]);
                                                                            scanf("%d", &confirmar_voto);

                                                                            if (confirmar_voto == 1){
                                                                                cont2[primeiro]++;
                                                                            }

                                                                            limpar_tela();
                                                                    } else if (voto == numero_candidato[segundo] ){
                                                                        printf("\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ", nome_candidato[segundo]);
                                                                            scanf("%d", &confirmar_voto);

                                                                            if (confirmar_voto == 1){
                                                                                cont2[segundo]++;
                                                                            }

                                                                            limpar_tela();
                                                                    } else {
                                                                        printf("\nVocê está votando Nulo. Para confirmar seu voto digite 1: ");
                                                                            scanf("%d", &confirmar_voto);

                                                                            if (confirmar_voto == 1){
                                                                                cont1[0] += 1;
                                                                            }

                                                                            limpar_tela();

                                                                    } //fim da votação

                                                        } while ( voto != 100);

                                                    }
                                                        //verificação segundo turno
                                                        if ( cont2[primeiro] > cont2[segundo] ){
                                                            printf("O candidato(a) %s venceu o 2° turno com %d votos.\n", nome_candidato[primeiro], cont2[primeiro]);
                                                        } else if ( cont2[segundo] > cont2[primeiro] ) {
                                                            printf("O candidato(a) %s venceu o 2° turno com %d votos.\n", nome_candidato[segundo], cont2[segundo]);
                                                        } else if ( cont2[primeiro] == cont2[segundo] ){
                                                            printf("\nEmpate. Desempate ocorrerá entre os candidatos %s e %s no formato (dd/mm/aaaa). \n", nome_candidato[primeiro], nome_candidato[segundo]);

                                                            pausar();
                                                                limpar_tela();

                                                            printf("Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ", nome_candidato[primeiro]);
                                                                scanf("%d/%d/%d", &dia[0], &mes[0], &ano[0]);
                                                                fflush(stdin);

                                                            printf("Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ", nome_candidato[segundo]);
                                                                scanf("%d/%d/%d", &dia[1], &mes[1], &ano[1]);
                                                                fflush(stdin);

                                                                if ( ano[0] < ano[1] ){
                                                                    printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                } else if ( ano[0] > ano[1]) {
                                                                    printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                } else { // anos diferentes -> comparar os meses
                                                                    if ( mes[0] < mes[1] ){
                                                                        printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                    } else if ( mes[0] > mes[1]) {
                                                                        printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                    } else { // meses iguais -> comparar os dias
                                                                        if ( dia[0] < dia[1] ){
                                                                            printf("O candidato(a) %s venceu.\n", nome_candidato[primeiro]);
                                                                        } else if ( dia[0] > dia[1]) {
                                                                            printf("O candidato(a) %s venceu.\n", nome_candidato[segundo]);
                                                                        }
                                                                    }
                                                                }

                                                        }
                                                        /*printf("Fim do programa.\n");
                                                        return 0;*/


                                                    } // fim do if resultado da votação
                                        } // fim do if

                            } while (0); // fim do "do" caso o numero_candidato[3] seja != 0

                    } else {
                            printf("Ainda não foram cadastrados candidatos. \n\n");
                    } // fim do if (numero_candidato[3] != 0)

                        pausar();
                            limpar_tela();

                } // fim do if (opcao_menu == 4)

            } while (opcao_menu != 5);

                if (opcao_menu == 5){
                    printf("Fim do programa.\n");
                }

    return 0;
}
