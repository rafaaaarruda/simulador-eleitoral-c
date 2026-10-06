#include <stdio.h>

#include "entrada.h"
#include "eleicao.h"
#include "terminal.h"

static int numero_candidato_ja_cadastrado(
    const Eleicao *eleicao,
    int indice_atual,
    int numero
) {
    for (int i = 0; i < indice_atual; i++) {
        if (eleicao->candidatos[i].numero == numero) {
            return 1;
        }
    }

    return 0;
}

void cadastrar_candidatos(Eleicao *eleicao) {
    char mensagem[100];

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        while (1) {
            snprintf(
                mensagem,
                sizeof(mensagem),
                "Digite o número do %d° candidato(a): ",
                i + 1
            );

            int numero = ler_inteiro(mensagem);

            if (numero <= 0) {
                printf("Número inválido. Digite um número positivo.\n");
                continue;
            }

            if (numero == 1 || numero == 100) {
                printf(
                    "Número indisponível. Os números 1 e 100 são reservados pelo sistema.\n"
                );
                continue;
            }

            if (numero_candidato_ja_cadastrado(eleicao, i, numero)) {
                printf("Número já cadastrado. Digite um número diferente.\n");
                continue;
            }

            eleicao->candidatos[i].numero = numero;
            break;
        }

        snprintf(
            mensagem,
            sizeof(mensagem),
            "Digite o nome do %d° candidato(a): ",
            i + 1
        );

        ler_nome(
            mensagem,
            eleicao->candidatos[i].nome,
            sizeof(eleicao->candidatos[i].nome)
        );

        puts(" ");
    }
}

static int solicitar_confirmacao_voto(const char *mensagem) {
    while (1) {
        int opcao = ler_inteiro(mensagem);

        if (opcao == 1) {
            return 1;
        }

        if (opcao == 0) {
            return 0;
        }

        printf(
            "Opção inválida. Digite 1 para confirmar ou 0 para cancelar.\n"
        );
    }
}

static void finalizar_confirmacao_voto(int confirmado) {
    if (confirmado) {
        printf("\nVoto confirmado.\n");
    } else {
        printf("\nVoto cancelado.\n");
    }

    pausar();
    limpar_tela();
}

void realizar_primeiro_turno(Eleicao *eleicao) {
    int voto;
    char mensagem_confirmacao[150];

    do {
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
            int confirmado = solicitar_confirmacao_voto(
                "\nVocê está votando Branco. Digite 1 para confirmar ou 0 para cancelar: "
            );

            if (confirmado) {
                eleicao->votos_brancos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[0].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[0].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->candidatos[0].votos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[1].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[1].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->candidatos[1].votos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[2].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[2].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->candidatos[2].votos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[3].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[3].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->candidatos[3].votos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else {
            int confirmado = solicitar_confirmacao_voto(
                "\nVocê está votando Nulo. Digite 1 para confirmar ou 0 para cancelar: "
            );

            if (confirmado) {
                eleicao->votos_nulos += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        }
    } while (voto != 100);
}

void realizar_segundo_turno(Eleicao *eleicao, int primeiro, int segundo) {
    int voto;
    char mensagem_confirmacao[150];

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        eleicao->votos_segundo_turno[i] = 0;
    }

    eleicao->votos_nulos_segundo_turno = 0;
    eleicao->votos_brancos_segundo_turno = 0;

    do {
        printf("----------Segundo Turno----------\n");
        printf("[1] - Voto Branco\n");
        printf(
            "[%d] - %s\n",
            eleicao->candidatos[primeiro].numero,
            eleicao->candidatos[primeiro].nome
        );
        printf(
            "[%d] - %s\n",
            eleicao->candidatos[segundo].numero,
            eleicao->candidatos[segundo].nome
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
            int confirmado = solicitar_confirmacao_voto(
                "\nVocê está votando Branco. Digite 1 para confirmar ou 0 para cancelar: "
            );

            if (confirmado) {
                eleicao->votos_brancos_segundo_turno += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[primeiro].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[primeiro].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->votos_segundo_turno[primeiro]++;
            }

            finalizar_confirmacao_voto(confirmado);
        } else if (voto == eleicao->candidatos[segundo].numero) {
            snprintf(
                mensagem_confirmacao,
                sizeof(mensagem_confirmacao),
                "\nVocê está votando no candidato(a) %s. Digite 1 para confirmar ou 0 para cancelar: ",
                eleicao->candidatos[segundo].nome
            );

            int confirmado = solicitar_confirmacao_voto(mensagem_confirmacao);

            if (confirmado) {
                eleicao->votos_segundo_turno[segundo]++;
            }

            finalizar_confirmacao_voto(confirmado);
        } else {
            int confirmado = solicitar_confirmacao_voto(
                "\nVocê está votando Nulo. Digite 1 para confirmar ou 0 para cancelar: "
            );

            if (confirmado) {
                eleicao->votos_nulos_segundo_turno += 1;
            }

            finalizar_confirmacao_voto(confirmado);
        }
    } while (voto != 100);
}

int identificar_empatados_na_lideranca(const Eleicao *eleicao, int empatados[]) {
    int maior_votacao = eleicao->candidatos[0].votos;
    int quantidade = 0;

    for (int i = 1; i < TOTAL_CANDIDATOS; i++) {
        if (eleicao->candidatos[i].votos > maior_votacao) {
            maior_votacao = eleicao->candidatos[i].votos;
        }
    }

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        if (eleicao->candidatos[i].votos == maior_votacao) {
            empatados[quantidade] = i;
            quantidade++;
        }
    }

    return quantidade;
}

static int comparar_datas_nascimento(
    int dia_a,
    int mes_a,
    int ano_a,
    int dia_b,
    int mes_b,
    int ano_b
) {
    if (ano_a != ano_b) {
        return ano_a < ano_b ? -1 : 1;
    }

    if (mes_a != mes_b) {
        return mes_a < mes_b ? -1 : 1;
    }

    if (dia_a != dia_b) {
        return dia_a < dia_b ? -1 : 1;
    }

    return 0;
}

static int selecionar_mais_velhos(
    const Eleicao *eleicao,
    const int candidatos[],
    int quantidade,
    int quantidade_selecionar,
    int selecionados[]
) {
    int dia[TOTAL_CANDIDATOS];
    int mes[TOTAL_CANDIDATOS];
    int ano[TOTAL_CANDIDATOS];
    int ordem[TOTAL_CANDIDATOS];
    char mensagem[150];

    for (int i = 0; i < quantidade; i++) {
        int indice = candidatos[i];
        ordem[i] = i;

        snprintf(
            mensagem,
            sizeof(mensagem),
            "Digite a data de nascimento do candidato(a) %s no formato (dd/mm/aaaa): ",
            eleicao->candidatos[indice].nome
        );

        ler_data(
            mensagem,
            &dia[i],
            &mes[i],
            &ano[i]
        );
    }

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            int posicao_i = ordem[i];
            int posicao_j = ordem[j];

            if (comparar_datas_nascimento(
                    dia[posicao_j], mes[posicao_j], ano[posicao_j],
                    dia[posicao_i], mes[posicao_i], ano[posicao_i]
                ) < 0) {
                int temporario = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = temporario;
            }
        }
    }

    if (quantidade_selecionar < quantidade) {
        int ultima_vaga = ordem[quantidade_selecionar - 1];
        int primeiro_fora = ordem[quantidade_selecionar];

        if (comparar_datas_nascimento(
                dia[ultima_vaga], mes[ultima_vaga], ano[ultima_vaga],
                dia[primeiro_fora], mes[primeiro_fora], ano[primeiro_fora]
            ) == 0) {
            return 0;
        }
    }

    for (int i = 0; i < quantidade_selecionar; i++) {
        selecionados[i] = candidatos[ordem[i]];
    }

    return 1;
}

int desempatar_por_idade(
    const Eleicao *eleicao,
    const int candidatos[],
    int quantidade
) {
    printf("Candidatos empatados:\n");
    for (int i = 0; i < quantidade; i++) {
        int indice = candidatos[i];
        printf(
            "- %s [%d]\n",
            eleicao->candidatos[indice].nome,
            eleicao->candidatos[indice].numero
        );
    }
    puts(" ");

    int vencedor;

    if (!selecionar_mais_velhos(eleicao, candidatos, quantidade, 1, &vencedor)) {
        printf(
            "\nO empate persiste: há candidatos empatados com a mesma data de nascimento.\n"
        );
        return -1;
    }

    printf("O candidato(a) %s venceu.\n", eleicao->candidatos[vencedor].nome);

    return vencedor;
}

int selecionar_finalistas_segundo_turno(
    const Eleicao *eleicao,
    int *primeiro,
    int *segundo
) {
    int lideres[TOTAL_CANDIDATOS];
    int quantidade_lideres = identificar_empatados_na_lideranca(eleicao, lideres);

    if (quantidade_lideres == 2) {
        *primeiro = lideres[0];
        *segundo = lideres[1];
        return 1;
    }

    if (quantidade_lideres > 2) {
        printf(
            "\nHá %d candidatos empatados na maior votação. "
            "As duas vagas do 2° turno serão definidas por idade.\n\n",
            quantidade_lideres
        );
        pausar();
        limpar_tela();

        printf("Candidatos empatados pelas vagas do 2° turno:\n");
        for (int i = 0; i < quantidade_lideres; i++) {
            int indice = lideres[i];
            printf(
                "- %s [%d]\n",
                eleicao->candidatos[indice].nome,
                eleicao->candidatos[indice].numero
            );
        }
        puts(" ");

        int selecionados[2];
        if (!selecionar_mais_velhos(
                eleicao,
                lideres,
                quantidade_lideres,
                2,
                selecionados
            )) {
            printf(
                "\nO empate pelas vagas do 2° turno persiste: "
                "há candidatos com a mesma data de nascimento na posição de corte.\n"
            );
            return 0;
        }

        *primeiro = selecionados[0];
        *segundo = selecionados[1];
        return 1;
    }

    *primeiro = lideres[0];

    int segunda_maior_votacao = -1;
    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        if (i != *primeiro && eleicao->candidatos[i].votos > segunda_maior_votacao) {
            segunda_maior_votacao = eleicao->candidatos[i].votos;
        }
    }

    int empatados_segunda_vaga[TOTAL_CANDIDATOS];
    int quantidade_segunda_vaga = 0;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        if (i != *primeiro && eleicao->candidatos[i].votos == segunda_maior_votacao) {
            empatados_segunda_vaga[quantidade_segunda_vaga] = i;
            quantidade_segunda_vaga++;
        }
    }

    if (quantidade_segunda_vaga == 1) {
        *segundo = empatados_segunda_vaga[0];
        return 1;
    }

    printf(
        "\nHá empate pela segunda vaga do 2° turno. O desempate ocorrerá por idade.\n\n"
    );
    pausar();
    limpar_tela();

    printf("Candidatos empatados pela segunda vaga:\n");
    for (int i = 0; i < quantidade_segunda_vaga; i++) {
        int indice = empatados_segunda_vaga[i];
        printf(
            "- %s [%d]\n",
            eleicao->candidatos[indice].nome,
            eleicao->candidatos[indice].numero
        );
    }
    puts(" ");

    int selecionado;
    if (!selecionar_mais_velhos(
            eleicao,
            empatados_segunda_vaga,
            quantidade_segunda_vaga,
            1,
            &selecionado
        )) {
        printf(
            "\nO empate pela segunda vaga do 2° turno persiste: "
            "há candidatos com a mesma data de nascimento.\n"
        );
        return 0;
    }

    *segundo = selecionado;
    return 1;
}

void exibir_resultados(const Eleicao *eleicao, int num_eleitores) {
    if (num_eleitores == 2) {
        for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
            printf(
                "Candidato(a) %s [%d] - %d votos\n",
                eleicao->candidatos[i].nome,
                eleicao->candidatos[i].numero,
                eleicao->candidatos[i].votos
            );
        }

        printf("Votos nulos - %d votos\n", eleicao->votos_nulos);
        printf("Votos brancos - %d votos\n", eleicao->votos_brancos);
    } else {
        for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
            printf(
                "Candidato(a) %s [%d] - %.2f%% com %d votos\n",
                eleicao->candidatos[i].nome,
                eleicao->candidatos[i].numero,
                eleicao->candidatos[i].percentual,
                eleicao->candidatos[i].votos
            );
        }

        printf(
            "Votos Nulos - %d e ocupa %.2f%% do total\n",
            eleicao->votos_nulos,
            eleicao->percentual_nulos
        );
        printf(
            "Votos Brancos - %d e ocupa %.2f%% do total\n",
            eleicao->votos_brancos,
            eleicao->percentual_brancos
        );
    }
}

void identificar_primeiro_segundo(const Eleicao *eleicao, int *primeiro, int *segundo) {
    *primeiro = 0;
    *segundo = 1;

    if (eleicao->candidatos[*segundo].votos > eleicao->candidatos[*primeiro].votos) {
        int temporario = *primeiro;
        *primeiro = *segundo;
        *segundo = temporario;
    }

    for (int i = 2; i < TOTAL_CANDIDATOS; i++) {
        if (eleicao->candidatos[i].votos > eleicao->candidatos[*primeiro].votos) {
            *segundo = *primeiro;
            *primeiro = i;
        } else if (eleicao->candidatos[i].votos > eleicao->candidatos[*segundo].votos) {
            *segundo = i;
        }
    }
}

int calcular_total_votos(const Eleicao *eleicao) {
    int total = eleicao->votos_nulos + eleicao->votos_brancos;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}

int calcular_total_votos_validos(const Eleicao *eleicao) {
    int total = 0;

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        total += eleicao->candidatos[i].votos;
    }

    return total;
}

void calcular_percentuais(Eleicao *eleicao) {
    int total_votos = calcular_total_votos(eleicao);
    int total_votos_validos = calcular_total_votos_validos(eleicao);

    for (int i = 0; i < TOTAL_CANDIDATOS; i++) {
        if (total_votos_validos > 0) {
            eleicao->candidatos[i].percentual =
                (eleicao->candidatos[i].votos * 100.0f) / total_votos_validos;
        } else {
            eleicao->candidatos[i].percentual = 0.0f;
        }
    }

    if (total_votos > 0) {
        eleicao->percentual_nulos =
            (eleicao->votos_nulos * 100.0f) / total_votos;

        eleicao->percentual_brancos =
            (eleicao->votos_brancos * 100.0f) / total_votos;
    } else {
        eleicao->percentual_nulos = 0.0f;
        eleicao->percentual_brancos = 0.0f;
    }
}
