#include "pesquisa.h"
#include "../Cadastro/cadastro.h"
#include "../Log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ABB global
static EABB* raizABB = NULL;

// Critérios de comparação
static int cmpAno(Paciente *a, Paciente *b)    { return a->ano  - b->ano; }
static int cmpMes(Paciente *a, Paciente *b)    { return a->mes  - b->mes; }
static int cmpDia(Paciente *a, Paciente *b)    { return a->dia  - b->dia; }
static int cmpIdade(Paciente *a, Paciente *b)  { return a->idade - b->idade; }

// Insere paciente na ABB (por ano, padrão)
void inserirNaABB(Paciente *pac) {
    EABB **p = &raizABB;
    while (*p) {
        if (cmpAno(pac, (*p)->dados) < 0) p = &((*p)->esq);
        else p = &((*p)->dir);
    }
    *p = (EABB*)malloc(sizeof(EABB));
    (*p)->dados = pac;
    (*p)->esq = NULL;
    (*p)->dir = NULL;

    // Log inserção
    char detalhes_json[256];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"rg\":\"%s\",\"ano\":%d,\"mes\":%d,\"dia\":%d,\"idade\":%d}",
        pac->nome, pac->rg, pac->ano, pac->mes, pac->dia, pac->idade);
    logarOperacao("INSERIR_ABB", detalhes_json);
}

void removerDaABB(Paciente* pac) {
    EABB **p = &raizABB;
    while (*p) {
        if (pac == (*p)->dados) {
            // Encontrou o nó a remover
            EABB *remover = *p;
            // Caso 1: sem filhos
            if (!remover->esq && !remover->dir) {
                free(remover);
                *p = NULL;
            }
            // Caso 2: só filho à direita
            else if (!remover->esq) {
                *p = remover->dir;
                free(remover);
            }
            // Caso 3: só filho à esquerda
            else if (!remover->dir) {
                *p = remover->esq;
                free(remover);
            }
            // Caso 4: dois filhos
            else {
                // Encontra o sucessor (menor da direita)
                EABB **suc = &(remover->dir);
                while ((*suc)->esq) suc = &((*suc)->esq);
                remover->dados = (*suc)->dados;
                EABB *tmp = *suc;
                *suc = (*suc)->dir;
                free(tmp);
            }
            return;
        }
        int cmp = cmpAno(pac, (*p)->dados);
        if (cmp < 0)
            p = &((*p)->esq);
        else
            p = &((*p)->dir);
    }
}

// Percursos in-ordem com critério customizável
static void in_ordem(EABB *raiz, int (*cmp)(Paciente*,Paciente*), int criterio) {
    if (raiz != NULL) {
        in_ordem(raiz->esq, cmp, criterio);
        Paciente *p = raiz->dados;
        printf("Nome: %s | RG: %s | Data: %02d/%02d/%04d | Idade: %d\n",
               p->nome, p->rg, p->dia, p->mes, p->ano, p->idade);
        char detalhes_json[256];
        snprintf(detalhes_json, sizeof(detalhes_json),
            "{\"nome\":\"%s\",\"rg\":\"%s\",\"ano\":%d,\"mes\":%d,\"dia\":%d,\"idade\":%d}",
            p->nome, p->rg, p->ano, p->mes, p->dia, p->idade);
        if (criterio == 1) logarOperacao("MOSTRAR_POR_ANO", detalhes_json);
        else if (criterio == 2) logarOperacao("MOSTRAR_POR_MES", detalhes_json);
        else if (criterio == 3) logarOperacao("MOSTRAR_POR_DIA", detalhes_json);
        else if (criterio == 4) logarOperacao("MOSTRAR_POR_IDADE", detalhes_json);
        in_ordem(raiz->dir, cmp, criterio);
    }
}

// Funções auxiliares para ABB temporária
static void inserirPorCriterio(EABB **raiz, Paciente *pac, int (*cmp)(Paciente*,Paciente*)) {
    while (*raiz) {
        if (cmp(pac, (*raiz)->dados) < 0) raiz = &((*raiz)->esq);
        else raiz = &((*raiz)->dir);
    }
    *raiz = (EABB*)malloc(sizeof(EABB));
    (*raiz)->dados = pac;
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;
}

static void percorrerEInserir(EABB *origem, EABB **destino, int (*cmp)(Paciente*,Paciente*)) {
    if (!origem) return;
    percorrerEInserir(origem->esq, destino, cmp);
    inserirPorCriterio(destino, origem->dados, cmp);
    percorrerEInserir(origem->dir, destino, cmp);
}

static void liberaABB(EABB *no) {
    if (no) {
        liberaABB(no->esq);
        liberaABB(no->dir);
        free(no);
    }
}

// Funções de mostrar ordenado
void mostrarPorAno() {
    printf("\n--- Pacientes ordenados por ANO de registro ---\n");
    in_ordem(raizABB, cmpAno, 1);
}
void mostrarPorMes() {
    printf("\n--- Pacientes ordenados por MÊS de registro ---\n");
    EABB *raizMes = NULL;
    percorrerEInserir(raizABB, &raizMes, cmpMes);
    in_ordem(raizMes, cmpMes, 2);
    liberaABB(raizMes);
}
void mostrarPorDia() {
    printf("\n--- Pacientes ordenados por DIA de registro ---\n");
    EABB *raizDia = NULL;
    percorrerEInserir(raizABB, &raizDia, cmpDia);
    in_ordem(raizDia, cmpDia, 3);
    liberaABB(raizDia);
}
void mostrarPorIdade() {
    printf("\n--- Pacientes ordenados por IDADE ---\n");
    EABB *raizIdade = NULL;
    percorrerEInserir(raizABB, &raizIdade, cmpIdade);
    in_ordem(raizIdade, cmpIdade, 4);
    liberaABB(raizIdade);
}

/* Sub-menu 4: Pesquisa / Ordenação via ABB */
void menuPesquisa() {
    int op;
    do {
        printf("\n--- Pesquisa / Ordenação (ABB) ---\n");
        printf("1. Ordenar por ano de registro\n");
        printf("2. Ordenar por mês de registro\n");
        printf("3. Ordenar por dia de registro\n");
        printf("4. Ordenar por idade do paciente\n");
        printf("0. Voltar\n");
        printf("---------------------------------\n");
        printf("Opção: ");
        scanf(" %d", &op);
        switch (op) {
            case 1: mostrarPorAno();    break;
            case 2: mostrarPorMes();    break;
            case 3: mostrarPorDia();    break;
            case 4: mostrarPorIdade();  break;
            case 0: /* volta */         break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}
