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
#include "eleicao.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao_menu, voto, senha = 1234, num_eleitores;
    int cont1[2] = {0, 0}, controle[4] = {0, 0, 0, 0};
    float percentual_nulos = 0, percentual_brancos = 0, total_votos, total_votos_validos;
    int confirmar_voto, idade[2] = {0, 0};
    Candidato candidatos[TOTAL_CANDIDATOS] = {0};
    int maior_voto = 0, segundo_maior_voto = 0;
    int primeiro = 0, segundo = 0, numero_valido = 0;
    int dia[2], mes[2], ano[2];
    char mensagem_confirmacao[150];

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
        if (opcao_menu == 1) {
            if (controle[0] == 1) {
                printf("Já foi feito o cadastro de candidatos.\n\n");
            } else {
                senha = ler_inteiro("Digite a senha: ");
                limpar_tela();
                while (senha != 1234) {
                    senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");
                    if (senha == 0) {
                        break;
                    }
                    limpar_tela();
                }
                if (senha == 1234) {
                    controle[0] = 1;
                    char mensagem[100];
                    for (int i = 0; i < 4; i++) {
                        snprintf(
                            mensagem,
                            sizeof(mensagem),
                            "Digite o número do %d° candidato(a): ",
                            i + 1
                        );
                        candidatos[i].numero = ler_inteiro(mensagem);
                        do {
                            if (numero_valido == 1) {
                                candidatos[i].numero = ler_inteiro(
                                    "Número do candidato(a) inválido. Digite novamente: "
                                );
                            }
                            for (int j = 0; j < 4; j++) {
                                if (i != j) {
                                    if (candidatos[i].numero == candidatos[j].numero) {
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
                            candidatos[i].nome,
                            sizeof(candidatos[i].nome)
                        );
                        puts(" ");
                    }
                } // fim senha
            } // fim controle
            pausar();
            limpar_tela();
        } // fim if 1
        if (opcao_menu == 2) {
            if (controle[1] == 1) {
                printf("Votação já foi encerrada. Compute os votos para saber o vencedor.\n\n");
            } else if (candidatos[3].numero != 0) {
                senha = ler_inteiro("Digite a senha: ");
                limpar_tela();
                while (senha != 1234) {
                    senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");
                    if (senha == 0) {
                        break;
                    }
                    limpar_tela();
                }
                if (senha == 1234) {
                    if (controle[3] != 1) {
                        printf("-------Qntd. de Eleitores-------\n");
                        printf("[1] + de 200k\n");
                        printf("[2] - de 200k\n");
                        num_eleitores = ler_inteiro("Digite uma opção: ");
                        while (num_eleitores != 1 && num_eleitores != 2) {
                            num_eleitores = ler_inteiro(
                                "Número de eleitores inválido. Digite novamente: "
                            );
                        }
                        pausar();
                        limpar_tela();
                    }
                    do {
                        controle[3] = 1;
                        printf("----------Primeiro turno----------\n");
                        printf("[1] - Voto Branco\n");
                        printf("[100] - Sair da votação\n");
                        voto = ler_inteiro(
                            "Digite o número do seu candidato(a) ou uma das opções acima: "
                        );
                        while (voto < 0) {
                            voto = ler_inteiro("\nVoto inválido. Digite novamente: ");
                        }
                        if (voto == 100) {
                            printf("\nFim da votação.\n\n");
                        } else if (voto == 1) {
                            confirmar_voto = ler_inteiro(
                                "\nVocê está votando Branco. Para confirmar seu voto digite 1: "
                            );
                            if (confirmar_voto == 1) {
                                cont1[1] += 1;
                            }
                            limpar_tela();
                        } else if (voto == candidatos[0].numero) {
                            snprintf(
                                mensagem_confirmacao,
                                sizeof(mensagem_confirmacao),
                                "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                candidatos[0].nome
                            );
                            confirmar_voto = ler_inteiro(mensagem_confirmacao);
                            if (confirmar_voto == 1) {
                                candidatos[0].votos += 1;
                            }
                            limpar_tela();
                        } else if (voto == candidatos[1].numero) {
                            snprintf(
                                mensagem_confirmacao,
                                sizeof(mensagem_confirmacao),
                                "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                candidatos[1].nome
                            );
                            confirmar_voto = ler_inteiro(mensagem_confirmacao);
                            if (confirmar_voto == 1) {
                                candidatos[1].votos += 1;
                            }
                            limpar_tela();
                        } else if (voto == candidatos[2].numero) {
                            snprintf(
                                mensagem_confirmacao,
                                sizeof(mensagem_confirmacao),
                                "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                candidatos[2].nome
                            );
                            confirmar_voto = ler_inteiro(mensagem_confirmacao);
                            if (confirmar_voto == 1) {
                                candidatos[2].votos += 1;
                            }
                            limpar_tela();
                        } else if (voto == candidatos[3].numero) {
                            snprintf(
                                mensagem_confirmacao,
                                sizeof(mensagem_confirmacao),
                                "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                candidatos[3].nome
                            );
                            confirmar_voto = ler_inteiro(mensagem_confirmacao);
                            if (confirmar_voto == 1) {
                                candidatos[3].votos += 1;
                            }
                            limpar_tela();
                        } else {
                            confirmar_voto = ler_inteiro(
                                "\nVocê está votando Nulo. Para confirmar seu voto digite 1: "
                            );
                            if (confirmar_voto == 1) {
                                cont1[0] += 1;
                            }
                            limpar_tela();
                        } // fim da votação
                    } while (voto != 100); // fim do "do" caso o numero_candidato[3] seja != 0
                } //fim senha
            } else {
                printf("Ainda não foram cadastrados candidatos. \n\n");
            } // fim do if (numero_candidato[3] != 0)
            pausar();
            limpar_tela();
        } // fim do if (opcao_menu == 2)
        if (opcao_menu == 3) {
            if (controle[1] == 1) {
                printf("A votação já foi encerrada. Compute os votos para saber o ganhador.\n\n");
            } else if (candidatos[0].votos == 0 && candidatos[1].votos == 0 && candidatos[2].votos == 0 && candidatos[3].votos == 0) {
                printf("Ainda não foi feita a eleição.\n\n");
            } else if (candidatos[3].numero != 0) {
                do {
                    senha = ler_inteiro("Digite a senha: ");
                    limpar_tela();
                    while (senha != 1234) {
                        senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");
                        if (senha == 0) {
                            break;
                        }
                        limpar_tela();
                    }
                    if (senha == 1234) {
                        controle[1] = 1;
                        total_votos = cont1[0] + cont1[1] + candidatos[0].votos + candidatos[1].votos + candidatos[2].votos + candidatos[3].votos;
                        for (int i = 0; i < 4; i++) {
                            candidatos[i].percentual = (candidatos[i].votos * 100) / total_votos;
                        }
                        percentual_nulos = (cont1[0] * 100) / total_votos; //votos nulos
                        percentual_brancos = (cont1[1] * 100) / total_votos; //votos brancos
                        printf("Votos encerrados.\n\n");
                    } // fim do if senha
                } while (0); // fim do "do" caso o numero_candidato[3] seja != 0
            } else {
                printf("Ainda não foram cadastrados candidatos. \n\n");
            } // fim do if (numero_candidato[3] != 0)
            pausar();
            limpar_tela();
        } // fim do if (opcao_menu == 3)
        if (opcao_menu == 4) {
            if (controle[2] == 1) {
                printf(
                    "O resultado da eleição já foi divulgado. O candidato(a) %s[%d] ganhou.\n\n",
                    candidatos[primeiro].nome,
                    candidatos[primeiro].numero
                );
            } else if (candidatos[0].votos == 0 && candidatos[1].votos == 0 && candidatos[2].votos == 0 && candidatos[3].votos == 0) {
                printf("Ainda não foi feita a eleição.\n\n");
            } else if (candidatos[0].percentual == 0 && candidatos[1].percentual == 0 && candidatos[2].percentual == 0 && candidatos[3].percentual == 0) {
                printf("Ainda não foi feita a contagem de votos.\n\n");
            } else if (candidatos[3].numero != 0) {
                do {
                    senha = ler_inteiro("Digite a senha: ");
                    limpar_tela();
                    while (senha != 1234) {
                        senha = ler_inteiro("Senha inválida. Digite novamente ou '0' para retornar ao menu: ");
                        if (senha == 0) {
                            break;
                        }
                        limpar_tela();
                    }
                    if (senha == 1234) {
                        controle[2] = 1;
                        if (num_eleitores == 2) {
                            for (int i = 0; i < 4; i++) {
                                printf(
                                    "Candidato(a) %s [%d] - %d votos\n",
                                    candidatos[i].nome,
                                    candidatos[i].numero,
                                    candidatos[i].votos
                                );
                            }
                            printf("Votos nulos - %d votos\n", cont1[0]);
                            printf("Votos brancos - %d votos\n", cont1[1]);
                        } else {
                            for (int i = 0; i < 4; i++) {
                                printf(
                                    "Candidato(a) %s [%d] - %.2f%% com %d votos\n",
                                    candidatos[i].nome,
                                    candidatos[i].numero,
                                    candidatos[i].percentual,
                                    candidatos[i].votos
                                );
                            }
                            printf("Votos Nulos - %d e ocupa %.2f%% do total\n", cont1[0], percentual_nulos);
                            printf("Votos Brancos - %d e ocupa %.f%% do total\n", cont1[1], percentual_brancos);
                        }
                        for (int i = 0; i < 4; i++) {
                            if (candidatos[i].votos > maior_voto) {
                                segundo_maior_voto = maior_voto;
                                maior_voto = candidatos[i].votos;
                                segundo = primeiro;
                                primeiro = i;
                            } else if (candidatos[i].votos > segundo_maior_voto) {
                                segundo_maior_voto = candidatos[i].votos;
                                segundo = i;
                            }
                        }
                        if (num_eleitores == 2) {
                            if (maior_voto == segundo_maior_voto) { //empatou 1° turno com - 200k eleitores
                                printf(
                                    "\nNão houve vencedor. Ocorrerá desempate por meio da idade dos candidatos %s e %s. \n\n",
                                    candidatos[primeiro].nome,
                                    candidatos[segundo].nome
                                );
                                pausar();
                                limpar_tela();
                                snprintf(
                                    mensagem_confirmacao,
                                    sizeof(mensagem_confirmacao),
                                    "Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ",
                                    candidatos[primeiro].nome
                                );
                                ler_data(
                                    mensagem_confirmacao,
                                    &dia[0],
                                    &mes[0],
                                    &ano[0]
                                );
                                snprintf(
                                    mensagem_confirmacao,
                                    sizeof(mensagem_confirmacao),
                                    "Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ",
                                    candidatos[segundo].nome
                                );
                                ler_data(
                                    mensagem_confirmacao,
                                    &dia[1],
                                    &mes[1],
                                    &ano[1]
                                );
                                if (ano[0] < ano[1]) {
                                    printf(
                                        "O candidato(a) %s venceu.\n",
                                        candidatos[primeiro].nome
                                    );
                                } else if (ano[0] > ano[1]) {
                                    printf(
                                        "O candidato(a) %s venceu.\n",
                                        candidatos[segundo].nome
                                    );
                                } else { // anos diferentes -> comparar os meses
                                    if (mes[0] < mes[1]) {
                                        printf(
                                            "O candidato(a) %s venceu.\n",
                                            candidatos[primeiro].nome
                                        );
                                    } else if (mes[0] > mes[1]) {
                                        printf(
                                            "O candidato(a) %s venceu.\n",
                                            candidatos[segundo].nome
                                        );
                                    } else { // meses iguais -> comparar os dias
                                        if (dia[0] < dia[1]) {
                                            printf(
                                                "O candidato(a) %s venceu.\n",
                                                candidatos[primeiro].nome
                                            );
                                        } else if (dia[0] > dia[1]) {
                                            printf(
                                                "O candidato(a) %s venceu.\n",
                                                candidatos[segundo].nome
                                            );
                                        }
                                    }
                                }
                            } else { // nao empatou -> houve um vencedor
                                printf(
                                    "O candidato(a) %s venceu o 1° turno.\n",
                                    candidatos[primeiro].nome
                                );
                            }
                        } else { // cidade tem mais de 200k eleitores
                            if (candidatos[primeiro].percentual > 50.0) { // if resultado da votação
                                printf(
                                    "O candidato(a) %s venceu o 1° turno com %.2f%% dos votos válidos.\n",
                                    candidatos[primeiro].nome,
                                    candidatos[primeiro].percentual
                                );
                            } else if (candidatos[primeiro].percentual < 50.0) {
                                printf(
                                    "\nNão houve vencedor no 1° turno. Ocorrerá 2° turno entre os candidatos %s e %s. \n\n",
                                    candidatos[primeiro].nome,
                                    candidatos[segundo].nome
                                );
                                pausar();
                                limpar_tela();
                                // votação do segundo turno
                                candidatos[primeiro].votos = 0;
                                candidatos[segundo].votos = 0;
                                //zerar o voto dos finalistas
                                do {
                                    printf("----------Segundo Turno----------\n");
                                    printf("[1] - Voto Branco\n");
                                    printf(
                                        "[%d] - %s\n",
                                        candidatos[primeiro].numero,
                                        candidatos[primeiro].nome
                                    );
                                    printf(
                                        "[%d] - %s\n",
                                        candidatos[segundo].numero,
                                        candidatos[segundo].nome
                                    );
                                    printf("[100] - Sair da votação\n");
                                    voto = ler_inteiro(
                                        "Digite o número do seu candidato(a) ou uma das opções acima: "
                                    );
                                    while (voto < 0) {
                                        voto = ler_inteiro("\nVoto inválido. Digite novamente: ");
                                    }
                                    if (voto == 100) {
                                        printf("\nFim da votação.\n\n");
                                    } else if (voto == 1) {
                                        confirmar_voto = ler_inteiro(
                                            "\nVocê está votando Branco. Para confirmar seu voto digite 1: "
                                        );
                                        if (confirmar_voto == 1) {
                                            cont1[1] += 1;
                                        }
                                        limpar_tela();
                                    } else if (voto == candidatos[primeiro].numero) {
                                        snprintf(
                                            mensagem_confirmacao,
                                            sizeof(mensagem_confirmacao),
                                            "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                            candidatos[primeiro].nome
                                        );
                                        confirmar_voto = ler_inteiro(mensagem_confirmacao);
                                        if (confirmar_voto == 1) {
                                            candidatos[primeiro].votos++;
                                        }
                                        limpar_tela();
                                    } else if (voto == candidatos[segundo].numero) {
                                        snprintf(
                                            mensagem_confirmacao,
                                            sizeof(mensagem_confirmacao),
                                            "\nVocê está votando no candidato(a) %s. Para confirmar seu voto digite 1: ",
                                            candidatos[segundo].nome
                                        );
                                        confirmar_voto = ler_inteiro(mensagem_confirmacao);
                                        if (confirmar_voto == 1) {
                                            candidatos[segundo].votos++;
                                        }
                                        limpar_tela();
                                    } else {
                                        confirmar_voto = ler_inteiro(
                                            "\nVocê está votando Nulo. Para confirmar seu voto digite 1: "
                                        );
                                        if (confirmar_voto == 1) {
                                            cont1[0] += 1;
                                        }
                                        limpar_tela();
                                    } //fim da votação
                                } while (voto != 100);
                            }
                            //verificação segundo turno
                            if (candidatos[primeiro].votos > candidatos[segundo].votos) {
                                printf(
                                    "O candidato(a) %s venceu o 2° turno com %d votos.\n",
                                    candidatos[primeiro].nome,
                                    candidatos[primeiro].votos
                                );
                            } else if (candidatos[segundo].votos > candidatos[primeiro].votos) {
                                printf(
                                    "O candidato(a) %s venceu o 2° turno com %d votos.\n",
                                    candidatos[segundo].nome,
                                    candidatos[segundo].votos
                                );
                            } else if (candidatos[primeiro].votos == candidatos[segundo].votos) {
                                printf(
                                    "\nEmpate. Desempate ocorrerá entre os candidatos %s e %s no formato (dd/mm/aaaa). \n",
                                    candidatos[primeiro].nome,
                                    candidatos[segundo].nome
                                );
                                pausar();
                                limpar_tela();
                                snprintf(
                                    mensagem_confirmacao,
                                    sizeof(mensagem_confirmacao),
                                    "Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ",
                                    candidatos[primeiro].nome
                                );
                                ler_data(
                                    mensagem_confirmacao,
                                    &dia[0],
                                    &mes[0],
                                    &ano[0]
                                );
                                snprintf(
                                    mensagem_confirmacao,
                                    sizeof(mensagem_confirmacao),
                                    "Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ",
                                    candidatos[segundo].nome
                                );
                                ler_data(
                                    mensagem_confirmacao,
                                    &dia[1],
                                    &mes[1],
                                    &ano[1]
                                );
                                if (ano[0] < ano[1]) {
                                    printf(
                                        "O candidato(a) %s venceu.\n",
                                        candidatos[primeiro].nome
                                    );
                                } else if (ano[0] > ano[1]) {
                                    printf(
                                        "O candidato(a) %s venceu.\n",
                                        candidatos[segundo].nome
                                    );
                                } else { // anos diferentes -> comparar os meses
                                    if (mes[0] < mes[1]) {
                                        printf(
                                            "O candidato(a) %s venceu.\n",
                                            candidatos[primeiro].nome
                                        );
                                    } else if (mes[0] > mes[1]) {
                                        printf(
                                            "O candidato(a) %s venceu.\n",
                                            candidatos[segundo].nome
                                        );
                                    } else { // meses iguais -> comparar os dias
                                        if (dia[0] < dia[1]) {
                                            printf(
                                                "O candidato(a) %s venceu.\n",
                                                candidatos[primeiro].nome
                                            );
                                        } else if (dia[0] > dia[1]) {
                                            printf(
                                                "O candidato(a) %s venceu.\n",
                                                candidatos[segundo].nome
                                            );
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
    if (opcao_menu == 5) {
        printf("Fim do programa.\n");
    }
    return 0;
}
