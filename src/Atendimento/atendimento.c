#include "atendimento.h"
#include "../Cadastro/cadastro.h"
#include "../Log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EFila {
    Paciente *dados;
    struct EFila *proximo;
} EFila;

typedef struct {
    EFila *head;
    EFila *tail;
    int qtde;
} Fila;

// crio a fila
static Fila filaAtendimento = {NULL, NULL, 0};

void enfileirarNormal() {
    char rg[20];
    printf("Digite o RG do paciente para enfileirar: ");
    scanf(" %[^\n]", rg);

    // Pega o paciente usando o numero de rg
    Paciente *pac = getPacientePorRG(rg);
    if (!pac) {
        logarOperacao("ENFILEIRAR", "{\"resultado\":\"nao encontrado\"}");
        return;
    }

    // criar a fila que recebe o novo paciente
    EFila *novo = (EFila*)malloc(sizeof(EFila));
    if (!novo) {
        printf("Erro de memória!\n");
        logarOperacao("ENFILEIRAR", "{\"resultado\":\"erro memoria\"}");
        return;
    }
    novo->dados = pac;
    novo->proximo = NULL;

    // adiciona o novo paaciente na fila principal
    if (filaAtendimento.qtde == 0) {
        filaAtendimento.head = novo;
    } else {
        filaAtendimento.tail->proximo = novo;
    }
    filaAtendimento.tail = novo;
    filaAtendimento.qtde++;

    printf("Paciente enfileirado para atendimento!\n");

    char detalhes_json[256];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"rg\":\"%s\"}", pac->nome, pac->rg);
    logarOperacao("ENFILEIRAR", detalhes_json);
}

void desenfileirarNormal() {
    if (filaAtendimento.qtde == 0) {
        printf("Fila vazia!\n");
        logarOperacao("DESENFILEIRAR", "{\"resultado\":\"fila vazia\"}");
        return;
    }
    // pega o primeiro da fila que vai ser removido
    EFila *remover = filaAtendimento.head;
    Paciente *pac = remover->dados;

    printf("Paciente chamado: %s | RG: %s\n", pac->nome, pac->rg);

    char detalhes_json[256];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"rg\":\"%s\"}", pac->nome, pac->rg);
    logarOperacao("DESENFILEIRAR", detalhes_json);

    // move a fila, e o primeiro passa a se o antigo segundo da fila
    filaAtendimento.head = remover->proximo;
    if (filaAtendimento.head == NULL)
        filaAtendimento.tail = NULL;
    free(remover);
    filaAtendimento.qtde--;
}

void mostrarFilaNormal() {
    if (filaAtendimento.qtde == 0) {
        printf("Fila vazia!\n");
        logarOperacao("MOSTRAR_FILA", "{\"resultado\":\"fila vazia\"}");
        return;
    }
    printf("Fila de pacientes para atendimento:\n");
    EFila *atual = filaAtendimento.head;
    int pos = 1;
    char detalhes_json[256];
    while (atual != NULL) {
        printf("%d. Nome: %s | RG: %s\n", pos, atual->dados->nome, atual->dados->rg);
        snprintf(detalhes_json, sizeof(detalhes_json),
            "{\"pos\":%d,\"nome\":\"%s\",\"rg\":\"%s\"}", pos, atual->dados->nome, atual->dados->rg);
        logarOperacao("MOSTRAR_FILA_ITEM", detalhes_json);
        atual = atual->proximo;
        pos++;
    }
    snprintf(detalhes_json, sizeof(detalhes_json), "{\"total\":%d}", filaAtendimento.qtde);
    logarOperacao("MOSTRAR_FILA", detalhes_json);
}

void menuAtendimento() {
    int op;
    do {
        printf("\n--- Atendimento Normal ---\n");
        printf("1. Enfileirar Paciente\n");
        printf("2. Desenfileirar Paciente\n");
        printf("3. Mostrar fila de Paciente\n");
        printf("0. Voltar\n");
        printf("-------------------------\n");
        printf("Opção: ");
        scanf(" %d", &op);
        switch (op) {
            case 1: enfileirarNormal(); break;
            case 2: desenfileirarNormal(); break;
            case 3: mostrarFilaNormal(); break;
            case 0: break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}
