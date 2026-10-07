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

static int autenticar_administrador(void) {
    const int senha_administrador = 1234;
    const char *mensagem = "Digite a senha ou '0' para retornar ao menu: ";

    while (1) {
        int senha = ler_inteiro(mensagem);
        limpar_tela();

        if (senha == 0) {
            printf("Operação cancelada. Retornando ao menu.\n\n");
            return 0;
        }

        if (senha == senha_administrador) {
            return 1;
        }

        mensagem = "Senha inválida. Digite novamente ou '0' para retornar ao menu: ";
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao_menu;
    int idade[2] = {0, 0};
    Eleicao eleicao = {.vencedor = -1};
    int primeiro = 0, segundo = 0;

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
        limpar_tela();

        if (opcao_menu == 1) {
            if (eleicao.candidatos_cadastrados == 1) {
                printf("Já foi feito o cadastro de candidatos.\n\n");
            } else {
                if (autenticar_administrador()) {
                    eleicao.candidatos_cadastrados = 1;
                    cadastrar_candidatos(&eleicao);
                } // fim senha
            } // fim controle
            pausar();
            limpar_tela();
        } // fim if 1
        if (opcao_menu == 2) {
            if (eleicao.votacao_encerrada == 1) {
                if (eleicao.resultado_divulgado == 1) {
                    printf("A votação já foi encerrada e o resultado já foi divulgado.\n\n");
                } else {
                    printf("A votação já foi encerrada. Compute os votos para saber o vencedor.\n\n");
                }
            } else if (eleicao.candidatos_cadastrados == 1) {
                if (autenticar_administrador()) {
                    if (eleicao.votacao_iniciada != 1) {
                        printf("-------Qntd. de Eleitores-------\n");
                        printf("[1] + de 200k\n");
                        printf("[2] - de 200k\n");
                        eleicao.faixa_eleitores = ler_inteiro("Digite uma opção: ");
                        while (eleicao.faixa_eleitores != 1 && eleicao.faixa_eleitores != 2) {
                            eleicao.faixa_eleitores = ler_inteiro(
                                "Número de eleitores inválido. Digite novamente: "
                            );
                        }
                        pausar();
                        limpar_tela();
                    }
                    eleicao.votacao_iniciada = 1;
                    realizar_primeiro_turno(&eleicao);
                } //fim senha
            } else {
                printf("Ainda não foram cadastrados candidatos. \n\n");
            } // fim do if (numero_candidato[3] != 0)
            pausar();
            limpar_tela();
        } // fim do if (opcao_menu == 2)
        if (opcao_menu == 3) {
            if (eleicao.candidatos_cadastrados == 0) {
                printf("Ainda não foram cadastrados candidatos.\n\n");
            } else if (eleicao.votacao_iniciada == 0) {
                printf("A votação ainda não foi iniciada.\n\n");
            } else if (eleicao.votacao_encerrada == 1) {
                if (eleicao.resultado_divulgado == 1) {
                    printf("A votação já foi encerrada e o resultado já foi divulgado.\n\n");
                } else {
                    printf("A votação já foi encerrada. Compute os votos para saber o vencedor.\n\n");
                }
            } else {
                do {
                    if (autenticar_administrador()) {
                        eleicao.votacao_encerrada = 1;
                        calcular_percentuais(&eleicao);
                        printf("Votação encerrada.\n\n");
                    } // fim do if senha
                } while (0);
            }
            pausar();
            limpar_tela();
        } // fim do if (opcao_menu == 3)
        if (opcao_menu == 4) {
            if (eleicao.resultado_divulgado == 1) {
                if (calcular_total_votos_validos(&eleicao) == 0) {
                    printf(
                        "O resultado da eleição já foi divulgado. Não houve votos válidos em candidatos.\n\n"
                    );
                } else {
                    printf(
                        "O resultado da eleição já foi divulgado. O candidato(a) %s[%d] ganhou.\n\n",
                        eleicao.candidatos[eleicao.vencedor].nome,
                        eleicao.candidatos[eleicao.vencedor].numero
                    );
                }
            } else if (eleicao.candidatos_cadastrados == 0) {
                printf("Ainda não foram cadastrados candidatos.\n\n");
            } else if (eleicao.votacao_iniciada == 0) {
                printf("A votação ainda não foi iniciada.\n\n");
            } else if (eleicao.votacao_encerrada == 0) {
                printf(
                    "A votação ainda não foi encerrada. Encerre a votação antes de computar os votos.\n\n"
                );
            } else {
                do {
                    if (autenticar_administrador()) {
                        exibir_resultados(&eleicao, eleicao.faixa_eleitores);

                        if (calcular_total_votos_validos(&eleicao) == 0) {
                            printf(
                                "\nNão houve votos válidos em candidatos. Não é possível determinar um vencedor.\n"
                            );
                            eleicao.resultado_divulgado = 1;
                            break;
                        }

                        identificar_primeiro_segundo(&eleicao, &primeiro, &segundo);

                        if (eleicao.faixa_eleitores == 2) {
                            int empatados[TOTAL_CANDIDATOS];
                            int quantidade_empatados = identificar_empatados_na_lideranca(
                                &eleicao,
                                empatados
                            );

                            if (quantidade_empatados > 1) {
                                printf(
                                    "\nHouve empate na maior votação. O desempate ocorrerá por idade.\n\n"
                                );
                                pausar();
                                limpar_tela();

                                int vencedor = desempatar_por_idade(
                                    &eleicao,
                                    empatados,
                                    quantidade_empatados
                                );

                                if (vencedor >= 0) {
                                    primeiro = vencedor;
                                    eleicao.vencedor = vencedor;
                                    eleicao.resultado_divulgado = 1;
                                }
                            } else {
                                primeiro = empatados[0];
                                eleicao.vencedor = primeiro;
                                eleicao.resultado_divulgado = 1;
                                printf(
                                    "O candidato(a) %s venceu o 1° turno.\n",
                                    eleicao.candidatos[primeiro].nome
                                );
                            }
                        } else { // cidade tem mais de 200k eleitores
                            if (eleicao.candidatos[primeiro].percentual > 50.0) { // if resultado da votação
                                eleicao.vencedor = primeiro;
                                eleicao.resultado_divulgado = 1;
                                printf(
                                    "O candidato(a) %s venceu o 1° turno com %.2f%% dos votos válidos.\n",
                                    eleicao.candidatos[primeiro].nome,
                                    eleicao.candidatos[primeiro].percentual
                                );
                            } else {
                                if (!selecionar_finalistas_segundo_turno(
                                        &eleicao,
                                        &primeiro,
                                        &segundo
                                    )) {
                                    break;
                                }

                                printf(
                                    "\nNão houve vencedor no 1° turno. Ocorrerá 2° turno entre os candidatos %s e %s. \n\n",
                                    eleicao.candidatos[primeiro].nome,
                                    eleicao.candidatos[segundo].nome
                                );
                                pausar();
                                limpar_tela();
                                realizar_segundo_turno(&eleicao, primeiro, segundo);

                                int total_votos_validos_segundo_turno =
                                    eleicao.votos_segundo_turno[primeiro] +
                                    eleicao.votos_segundo_turno[segundo];

                                if (total_votos_validos_segundo_turno == 0) {
                                    printf(
                                        "\nNão houve votos válidos no 2° turno. Não é possível determinar um vencedor.\n"
                                    );
                                    break;
                                }

                                //verificação segundo turno
                                if (eleicao.votos_segundo_turno[primeiro] > eleicao.votos_segundo_turno[segundo]) {
                                    eleicao.vencedor = primeiro;
                                    eleicao.resultado_divulgado = 1;
                                    printf(
                                        "O candidato(a) %s venceu o 2° turno com %d votos.\n",
                                        eleicao.candidatos[primeiro].nome,
                                        eleicao.votos_segundo_turno[primeiro]
                                    );
                                } else if (eleicao.votos_segundo_turno[segundo] > eleicao.votos_segundo_turno[primeiro]) {
                                    eleicao.vencedor = segundo;
                                    eleicao.resultado_divulgado = 1;
                                    printf(
                                        "O candidato(a) %s venceu o 2° turno com %d votos.\n",
                                        eleicao.candidatos[segundo].nome,
                                        eleicao.votos_segundo_turno[segundo]
                                    );
                                } else if (eleicao.votos_segundo_turno[primeiro] == eleicao.votos_segundo_turno[segundo]) {
                                    printf(
                                        "\nEmpate. Desempate ocorrerá entre os candidatos %s e %s no formato (dd/mm/aaaa). \n",
                                        eleicao.candidatos[primeiro].nome,
                                        eleicao.candidatos[segundo].nome
                                    );
                                    pausar();
                                    limpar_tela();

                                    int empatados_segundo_turno[2] = {primeiro, segundo};
                                    int vencedor = desempatar_por_idade(
                                        &eleicao,
                                        empatados_segundo_turno,
                                        2
                                    );

                                    if (vencedor >= 0) {
                                        primeiro = vencedor;
                                        eleicao.vencedor = vencedor;
                                        eleicao.resultado_divulgado = 1;
                                    }
                                }
                                /*printf("Fim do programa.\n");
                                return 0;*/
                            }
                        } // fim do if resultado da votação
                    } // fim do if
                } while (0);
            }
            pausar();
            limpar_tela();
        } // fim do if (opcao_menu == 4)
    } while (opcao_menu != 5);
    if (opcao_menu == 5) {
        printf("Fim do programa.\n");
    }
    return 0;
}
