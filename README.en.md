[🇧🇷 Português](README.md) | 🇺🇸 English

# 🗳️ Electoral Simulator in C

Electoral simulator developed in **C** and executed through the terminal, featuring candidate registration, vote recording, result tallying, a second round, and different tie-handling scenarios.

The project was originally developed as an academic assignment in **2024.2** and revisited in **2026**, mainly as a way to practice **Git and GitHub through a development workflow closer to a real software project**.

During this revision, the original implementation was preserved while the current version evolved gradually through branches, commits, and pull requests, along with logic fixes, modularization, validation improvements, and testing.

> This is an academic simulation. The implemented rules are part of the simulator's proposal and are not intended to fully reproduce Brazilian electoral law.

---

## 📌 About the project

The first version of the simulator was developed in 2024.2 as a single C program.

In 2026, I revisited the project mainly to practice **Git and GitHub in an applied way**, using the existing codebase to work with branches, incremental commits, pull requests, fixes, and reviews.

Throughout this process, I also improved the original implementation while preserving its proposal and keeping a copy of the academic version.

The revision included:

- organizing development through branches and pull requests;
- creating small and incremental commits;
- code modularization;
- structures to represent candidates and the election;
- stronger input validation;
- fixes to voting and tallying flows;
- edge-case handling;
- scenario testing;
- final code quality review.

The original academic version remains available at:

[`original/urna_eletronica_2024.c`](original/urna_eletronica_2024.c)

---

## ⚙️ Features

The simulator allows users to:

- register four candidates;
- validate candidate names and numbers;
- prevent duplicate or reserved candidate numbers;
- start and close voting;
- leave an open voting session and resume it later;
- record candidate votes;
- record blank and null votes;
- confirm or cancel a vote before registration;
- calculate votes and percentages;
- tally first-round results;
- run a second round in the scenarios defined by the simulation;
- resolve ties using age as a tie-breaker;
- handle a final tie when age cannot resolve the result;
- handle elections that end without a winner;
- prevent actions that are incompatible with the current election state.

---

## 🗳️ Election flow

The main program flow is:

```text
Register candidates
        ↓
Start voting
        ↓
Record votes
        ↓
Close voting
        ↓
Tally votes
        ↓
Result
        ↓
Second round / tie-break, when required
```

While voting remains open, the user can return to the main menu without officially closing the election and resume voting later.

---

## 📊 Simulation rules

Before voting starts, the program allows the user to select between two scenarios:

- locality with **more than 200 thousand voters**;
- locality with **fewer than 200 thousand voters**.

In the scenario with more than 200 thousand voters, a candidate must receive **more than 50% of the valid candidate votes** to win in the first round.

Otherwise, the selected candidates proceed to a second round.

In the scenario with fewer than 200 thousand voters, the candidate with the highest number of valid votes wins.

When a tie occurs in a decisive position, the simulator uses age as the tie-breaker, prioritizing the older candidate.

If the candidates also have the same date of birth, the election is recorded as a **final tie**.

Blank and null votes are counted separately and are not included in the candidates' percentage calculation.

---

## 📁 Project structure

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

### Main modules

| File | Responsibility |
|---|---|
| `main.c` | controls the menu and the main election flow |
| `eleicao.c` | handles registration, voting, tallying, and tie-breaking |
| `entrada.c` | handles input reading and validation |
| `terminal.c` | handles terminal-related operations |
| `include/` | contains shared structures, constants, and declarations |

---

## 🛡️ Input validation

The revised version uses line-based input and handles several invalid input situations, including:

- text entered when a number is expected;
- numbers outside the supported range;
- empty or invalid names;
- names above the allowed limit;
- lines larger than the input buffer;
- dates outside the expected format;
- invalid calendar dates;
- leap years;
- duplicate candidate numbers;
- numbers reserved by the system;
- invalid confirmation options.

---

## ▶️ How to run

### Requirements

A C compiler such as **Clang** or **GCC** is required.

### Clang

From the project root:

```bash
clang src/main.c src/terminal.c src/entrada.c src/eleicao.c \
-Iinclude -Wall -Wextra -Wpedantic \
-o simulador-eleitoral
```

Run:

```bash
./simulador-eleitoral
```

### GCC

```bash
gcc src/main.c src/terminal.c src/entrada.c src/eleicao.c \
-Iinclude -Wall -Wextra -Wpedantic \
-o simulador-eleitoral
```

Run:

```bash
./simulador-eleitoral
```

> The demonstration password used for administrative operations is `1234`.

---

## 🧪 Testing and quality

During the revision, different simulator scenarios were tested, including:

- candidate registration and validation;
- authentication;
- valid, blank, null, and canceled votes;
- resuming and closing voting;
- actions performed in invalid states;
- first-round victory;
- the exact 50% scenario;
- second round;
- ties involving multiple candidates;
- age-based tie-breaking;
- final ties;
- elections with no valid votes;
- invalid inputs and edge cases;
- input length limits;
- preservation of votes between rounds.

In addition to behavioral testing, the code was reviewed using additional compiler warnings, sanitizers, and Clang static analysis.

At the end of the revision, the project builds without warnings using:

```text
-Wall
-Wextra
-Wpedantic
```

---

## 🔄 Project evolution

### 2024.2 — academic version

The original implementation concentrated the entire logic in a single file and already included the main requirements of the assignment:

- candidate registration;
- voting;
- result tallying;
- basic simulator rules.

This version was preserved inside the `original/` directory.

### 2026 — incremental revision

The current version was gradually built on top of the existing project.

The main changes include:

- separation into `.c` and `.h` modules;
- creation of `Candidato` and `Eleicao` structures;
- centralized calculations;
- stronger input validation;
- separation of first- and second-round votes;
- fixes to result tallying flows;
- handling of multiple tie scenarios;
- explicit election states;
- scenario and edge-case testing;
- warning and obsolete-code cleanup.

Development was also organized through a workflow based on:

```text
branch
  ↓
incremental changes
  ↓
commits
  ↓
push
  ↓
pull request
  ↓
code review
  ↓
merge into develop
```

The goal was to use an existing project as a practical way to learn not only how to change code, but also how software can evolve through a structured version control workflow.

---

## 🌿 Git and GitHub

One of the main goals of revisiting the project was to practice Git and GitHub throughout a complete development process.

The workflow involved concepts such as:

- creating and switching branches;
- separating changes by responsibility;
- small and descriptive commits;
- synchronization between local and remote repositories;
- `git fetch` and `git pull`;
- remote-tracking branches;
- pull requests;
- merge commits;
- reviewing differences before commits;
- dedicated branches for features, fixes, testing, quality, and documentation.

The adopted workflow used `develop` as the integration branch before the final version reached `main`.

---

## 🧠 Concepts practiced

### C development

- structs;
- pointers;
- arrays;
- modularization;
- `.c` and `.h` files;
- input validation;
- state management;
- edge-case handling;
- terminal-based compilation.

### Version control

- Git;
- GitHub;
- branches;
- commits;
- local and remote repositories;
- pull requests;
- merges;
- incremental change review.

---

## 🎓 Context

Project originally developed in **2024.2** during college and revisited in **2026** as a practical experience in evolving an existing project, with a primary focus on **Git and GitHub** and incremental code improvement.
