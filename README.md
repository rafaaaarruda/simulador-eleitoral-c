🇧🇷 Português | [🇺🇸 English](README.en.md)

# 🗳️ Simulador Eleitoral em C

Simulador eleitoral desenvolvido em **C** e executado pelo terminal, com cadastro de candidatos, registro de votos, apuração, segundo turno e tratamento de diferentes cenários de empate.

O projeto foi desenvolvido originalmente como trabalho acadêmico em **2024.2** e retomado em **2026**, principalmente como uma forma de praticar **Git e GitHub em um fluxo de desenvolvimento mais próximo de um projeto real**.

Durante essa revisão, a implementação original foi preservada e a versão atual evoluiu gradualmente por meio de branches, commits e pull requests, junto com correções de lógica, modularização, validações e testes.

> Este projeto é uma simulação acadêmica. As regras implementadas fazem parte da proposta do simulador e não têm como objetivo reproduzir integralmente a legislação eleitoral brasileira.

---

## 📌 Sobre o projeto

A primeira versão do simulador foi desenvolvida em 2024.2 como um único programa em C.

Em 2026, retomei o projeto principalmente para praticar **Git e GitHub de forma aplicada**, utilizando o próprio código como base para trabalhar com branches, commits incrementais, pull requests, correções e revisões.

Ao longo desse processo, também aproveitei para melhorar a implementação original, mantendo sua proposta e preservando uma cópia da versão acadêmica.

A revisão incluiu:

- organização do desenvolvimento com branches e pull requests;
- criação de commits pequenos e incrementais;
- modularização do código;
- criação de estruturas para representar candidatos e a eleição;
- melhoria das validações de entrada;
- correções nos fluxos de votação e apuração;
- tratamento de casos de borda;
- testes de diferentes cenários;
- revisão final de qualidade.

A versão acadêmica original permanece disponível em:

[`original/urna_eletronica_2024.c`](original/urna_eletronica_2024.c)

---

## ⚙️ Funcionalidades

O simulador permite:

- cadastrar quatro candidatos;
- validar nomes e números dos candidatos;
- impedir números duplicados ou reservados;
- iniciar e encerrar a votação;
- sair de uma votação ainda aberta e retomá-la posteriormente;
- registrar votos em candidatos;
- registrar votos brancos e nulos;
- confirmar ou cancelar um voto antes do registro;
- calcular votos e percentuais;
- realizar a apuração do primeiro turno;
- realizar segundo turno nos cenários previstos pela simulação;
- resolver empates utilizando idade como critério;
- tratar empate final quando o critério de idade também não resolve;
- tratar eleições encerradas sem vencedor;
- impedir ações incompatíveis com o estado atual da eleição.

---

## 🗳️ Fluxo da eleição

O fluxo principal do programa é:

```text
Cadastrar candidatos
        ↓
Iniciar votação
        ↓
Registrar votos
        ↓
Encerrar votação
        ↓
Computar votos
        ↓
Resultado
        ↓
Segundo turno / desempate, quando necessário
```

Durante uma votação aberta, é possível retornar ao menu sem encerrá-la oficialmente e retomá-la depois.

---

## 📊 Regras utilizadas na simulação

Antes da votação, o programa permite selecionar entre duas situações:

- localidade com **mais de 200 mil eleitores**;
- localidade com **menos de 200 mil eleitores**.

No cenário com mais de 200 mil eleitores, um candidato precisa obter **mais de 50% dos votos válidos em candidatos** para vencer no primeiro turno.

Caso isso não aconteça, os candidatos classificados seguem para o segundo turno.

No cenário com menos de 200 mil eleitores, vence o candidato com maior número de votos válidos.

Quando existe empate em uma posição decisiva, o simulador utiliza a idade como critério de desempate, priorizando o candidato mais velho.

Se os candidatos também tiverem a mesma data de nascimento, o resultado é registrado como **empate final**.

Votos brancos e nulos são contabilizados separadamente e não entram no cálculo do percentual dos candidatos.

---

## 📁 Estrutura do projeto

```text
simulador-eleitoral-c/
├── include/
│   ├── eleicao.h
│   ├── entrada.h
│   └── terminal.h
├── original/
│   └── urna_eletronica_2024.c
├── src/
│   ├── eleicao.c
│   ├── entrada.c
│   ├── main.c
│   └── terminal.c
├── .gitignore
├── README.md
└── README.en.md
```

### Principais módulos

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | controla o menu e o fluxo principal da eleição |
| `eleicao.c` | concentra cadastro, votação, apuração e desempates |
| `entrada.c` | realiza leitura e validação das entradas |
| `terminal.c` | controla operações relacionadas ao terminal |
| `include/` | contém estruturas, constantes e declarações compartilhadas |

---

## 🛡️ Validação de entradas

A versão revisada utiliza leitura baseada em linhas e trata diferentes situações de entrada inválida, como:

- texto digitado onde é esperado um número;
- números fora do intervalo suportado;
- nomes vazios ou inválidos;
- nomes acima do limite permitido;
- linhas maiores que o buffer;
- datas fora do formato esperado;
- datas inexistentes;
- anos bissextos;
- números de candidato duplicados;
- números reservados pelo sistema;
- opções de confirmação inválidas.

---

## ▶️ Como executar

### Requisitos

É necessário ter um compilador C instalado, como **Clang** ou **GCC**.

### Clang

Na raiz do projeto:

```bash
clang src/main.c src/terminal.c src/entrada.c src/eleicao.c \
-Iinclude -Wall -Wextra -Wpedantic \
-o simulador-eleitoral
```

Execute:

```bash
./simulador-eleitoral
```

### GCC

```bash
gcc src/main.c src/terminal.c src/entrada.c src/eleicao.c \
-Iinclude -Wall -Wextra -Wpedantic \
-o simulador-eleitoral
```

Execute:

```bash
./simulador-eleitoral
```

> A senha de demonstração utilizada nas operações administrativas é `1234`.

---

## 🧪 Testes e qualidade

Durante a revisão, foram testados diferentes cenários do simulador, incluindo:

- cadastro e validação dos candidatos;
- autenticação;
- votos válidos, brancos, nulos e cancelados;
- retomada e encerramento da votação;
- ações executadas em estados inválidos;
- vitória no primeiro turno;
- cenário com exatamente 50% dos votos;
- segundo turno;
- empates entre múltiplos candidatos;
- desempate por idade;
- empate final;
- eleição sem votos válidos;
- entradas inválidas e casos de borda;
- limites de tamanho das entradas;
- preservação dos votos entre os turnos.

Além dos testes de comportamento, o código também foi revisado com avisos adicionais do compilador, sanitizers e análise estática do Clang.

Ao final da revisão, o projeto compila sem warnings utilizando:

```text
-Wall
-Wextra
-Wpedantic
```

---

## 🔄 Evolução do projeto

### 2024.2 — versão acadêmica

A implementação original concentrava toda a lógica em um único arquivo e já contemplava a proposta principal do trabalho:

- cadastro de candidatos;
- votação;
- apuração;
- regras básicas do simulador.

Essa versão foi preservada na pasta `original/`.

### 2026 — revisão incremental

A nova versão foi construída gradualmente sobre o projeto existente.

Entre as principais mudanças estão:

- separação em módulos `.c` e `.h`;
- criação das estruturas `Candidato` e `Eleicao`;
- centralização dos cálculos;
- melhorias na validação de entradas;
- separação dos votos do primeiro e segundo turno;
- correção dos fluxos de apuração;
- tratamento de múltiplos cenários de empate;
- estados explícitos da eleição;
- testes de cenários e casos de borda;
- revisão de warnings e código obsoleto.

O desenvolvimento também foi organizado utilizando um fluxo com:

```text
branch
  ↓
alterações incrementais
  ↓
commits
  ↓
push
  ↓
pull request
  ↓
code review
  ↓
merge em develop
```

A ideia foi utilizar um projeto antigo como base para praticar não apenas alterações no código, mas também o processo de evolução e versionamento de um software.

---

## 🌿 Git e GitHub

Um dos principais objetivos da retomada do projeto foi praticar Git e GitHub durante um processo completo de desenvolvimento.

Foram utilizados conceitos como:

- criação e troca de branches;
- separação de mudanças por responsabilidade;
- commits pequenos e descritivos;
- sincronização entre repositório local e remoto;
- `git fetch` e `git pull`;
- acompanhamento de branches remotas;
- pull requests;
- merge commits;
- revisão de diferenças antes dos commits;
- branches específicas para funcionalidades, correções, testes, qualidade e documentação.

O fluxo adotado utilizou a `develop` como branch de integração das alterações antes da versão final em `main`.

---

## 🧠 Conceitos praticados

### Desenvolvimento em C

- structs;
- ponteiros;
- arrays;
- modularização;
- arquivos `.c` e `.h`;
- validação de entradas;
- gerenciamento de estado;
- tratamento de casos de borda;
- compilação via terminal.

### Versionamento

- Git;
- GitHub;
- branches;
- commits;
- repositório local e remoto;
- pull requests;
- merges;
- revisão incremental de alterações.

---

## 🎓 Contexto

Projeto desenvolvido originalmente em **2024.2** durante a graduação e retomado em **2026** como uma experiência prática de evolução de um projeto existente, com foco principalmente no uso de **Git e GitHub** e na melhoria incremental do código.
