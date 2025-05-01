
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medico.h"

/*=== Estruturas internas ===*/
typedef struct NoLista {
    Paciente *pac;
    struct NoLista *prox;
} NoLista;
static NoLista *inicioLista = NULL, *fimLista = NULL;

typedef struct NoFila {
    Paciente *pac;
    struct NoFila *prox;
} NoFila;
static NoFila *inicioFila = NULL, *fimFila = NULL;
static int tamFila = 0;

typedef struct NoDesfazer {
    int tipo;            /* 0=enfileirou, 1=desenfileirou */
    Paciente *pac;
    struct NoDesfazer *prox;
} NoDesfazer;
static NoDesfazer *pilhaDesfazer = NULL;

static Paciente *heapPrioritario[MAX_DIARIO];
static int tamHeap = 0;

typedef struct NoABB {
    Paciente *pac;
    struct NoABB *esq, *dir;
} NoABB;
static NoABB *raizABB = NULL;

/*==== Auxiliares ====*/
static Paciente* buscarPorRG(const char *rg) {
    for (NoLista *p = inicioLista; p; p = p->prox)
        if (strcmp(p->pac->rg, rg) == 0)
            return p->pac;
    return NULL;
}

static void empilharOperacao(int tipo, Paciente *pac) {
    NoDesfazer *n = malloc(sizeof *n);
    n->tipo = tipo;
    n->pac  = pac;
    n->prox = pilhaDesfazer;
    pilhaDesfazer = n;
}

/*==== Cadastro ====*/
void cadastrarPaciente() {
    printf("\n===== CADASTRO DE PACIENTE =====\n");
    Paciente *p = malloc(sizeof *p);

    printf("Nome.......: ");
    scanf(" %99[^\n]", p->nome);

    printf("Idade......: ");
    scanf(" %d", &p->idade);

    printf("RG.........: ");
    scanf(" %19s", p->rg);

    printf("Data (d m a): ");
    scanf(" %d %d %d", &p->dia, &p->mes, &p->ano);

    NoLista *n = malloc(sizeof *n);
    n->pac  = p;
    n->prox = inicioLista;
    inicioLista = n;
    if (!fimLista) fimLista = n;

    printf("> Paciente “%s” cadastrado com sucesso!\n", p->nome);
}

/*==== Consulta ====*/
void consultarPaciente() {
    printf("\n===== CONSULTA DE PACIENTE =====\n");
    char rg[20];
    printf("Informe o RG: ");
    scanf(" %19s", rg);

    Paciente *p = buscarPorRG(rg);
    if (!p) {
        printf("⚠️  Paciente com RG “%s” não encontrado.\n", rg);
        return;
    }

    printf("\nDados do paciente:\n");
    printf("------------------------------\n");
    printf("Nome.......: %s\n", p->nome);
    printf("Idade......: %d anos\n", p->idade);
    printf("RG.........: %s\n", p->rg);
    printf("Entrada....: %02d/%02d/%04d\n", p->dia, p->mes, p->ano);
    printf("------------------------------\n");
}

/*==== Listagem ====*/
void listarPacientes() {
    printf("\n===== LISTA DE PACIENTES =====\n");
    if (!inicioLista) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    for (NoLista *p = inicioLista; p; p = p->prox) {
        printf("- %s | %d anos | RG %s | Entrada %02d/%02d/%04d\n",
               p->pac->nome, p->pac->idade, p->pac->rg,
               p->pac->dia, p->pac->mes, p->pac->ano);
    }
}

/*==== Atualização ====*/
void atualizarPaciente() {
    printf("\n===== ATUALIZAR PACIENTE =====\n");
    char rg[20];
    printf("Informe o RG: ");
    scanf(" %19s", rg);

    Paciente *p = buscarPorRG(rg);
    if (!p) {
        printf("⚠️  Paciente com RG “%s” não encontrado.\n", rg);
        return;
    }

    printf("Novo nome....: ");
    scanf(" %99[^\n]", p->nome);
    printf("Nova idade...: ");
    scanf(" %d", &p->idade);
    printf("Novo RG......: ");
    scanf(" %19s", p->rg);
    printf("Nova data....: ");
    scanf(" %d %d %d", &p->dia, &p->mes, &p->ano);

    printf("> Dados atualizados com sucesso!\n");
}

/*==== Remoção ====*/
void removerPaciente() {
    printf("\n===== REMOVER PACIENTE =====\n");
    char rg[20];
    printf("Informe o RG: ");
    scanf(" %19s", rg);

    NoLista *p = inicioLista, *ant = NULL;
    while (p && strcmp(p->pac->rg, rg)) {
        ant = p; p = p->prox;
    }
    if (!p) {
        printf("⚠️  Paciente com RG “%s” não encontrado.\n", rg);
        return;
    }

    if (ant) ant->prox = p->prox;
    else     inicioLista = p->prox;
    if (p == fimLista) fimLista = ant;
    free(p->pac);
    free(p);

    printf("> Paciente removido com sucesso!\n");
}
