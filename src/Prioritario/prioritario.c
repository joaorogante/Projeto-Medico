#include "prioritario.h"
#include "../Cadastro/cadastro.h"
#include "../Log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP 20

typedef struct {
    Paciente* dados[MAX_HEAP];
    int qtde;
} Heap;

static Heap heapPrioritario = { .qtde = 0 };

// funcoes auxiliares para calcular indices da heap binaria
int filho_esq(int pai) { return (2 * pai) + 1; }
int filho_dir(int pai) { return (2 * pai) + 2; }
int pai(int filho) { return (filho - 1) / 2; }

void peneirar(Heap *h, int p) {
    int maior = p;
    int e = filho_esq(p);
    int d = filho_dir(p);

    // verifica se o filho da esquerda eh maior que o atual
    if (e < h->qtde && h->dados[e]->idade > h->dados[maior]->idade)
        maior = e;

    // verifica se o filho da direita eh maior que o maior atual
    if (d < h->qtde && h->dados[d]->idade > h->dados[maior]->idade)
        maior = d;

    // se algum filho for maior, troca e chama recursivamente
    if (maior != p) {
        Paciente* temp = h->dados[p];
        h->dados[p] = h->dados[maior];
        h->dados[maior] = temp;
        peneirar(h, maior);
    }
}

void enfileirarPrioritario() {
    // confere se o heap ta cheio
    if (heapPrioritario.qtde >= MAX_HEAP) {
        printf("Fila prioritaria cheia!\n");
        logarOperacao("ENFILEIRAR_PRIORITARIO", "{\"resultado\":\"fila cheia\"}");
        return;
    }

    // pega o paciente pelo rg
    char rg[20];
    printf("Digite o RG do paciente para enfileirar prioritario: ");
    scanf(" %[^\n]", rg);

    Paciente* pac = getPacientePorRG(rg);
    if (!pac) {
        logarOperacao("ENFILEIRAR_PRIORITARIO", "{\"resultado\":\"nao encontrado\"}");
        return;
    }

    // insere o paciente na ultima posicao e sobe ele
    heapPrioritario.dados[heapPrioritario.qtde] = pac;
    int atual = heapPrioritario.qtde;
    heapPrioritario.qtde++;

    // sobe o paciente ate encontrar a posicao correta
    while (atual > 0 && heapPrioritario.dados[atual]->idade > heapPrioritario.dados[pai(atual)]->idade) {
        Paciente* temp = heapPrioritario.dados[atual];
        heapPrioritario.dados[atual] = heapPrioritario.dados[pai(atual)];
        heapPrioritario.dados[pai(atual)] = temp;
        atual = pai(atual);
    }

    printf("Paciente enfileirado prioritariamente!\n");

    // loga
    char detalhes_json[256];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"rg\":\"%s\",\"idade\":%d}", pac->nome, pac->rg, pac->idade);
    logarOperacao("ENFILEIRAR_PRIORITARIO", detalhes_json);
}

void desenfileirarPrioritario() {
    // se a heap estiver vazia, aviso e log
    if (heapPrioritario.qtde == 0) {
        printf("Fila prioritaria vazia!\n");
        logarOperacao("DESENFILEIRAR_PRIORITARIO", "{\"resultado\":\"fila vazia\"}");
        return;
    }

    // pega o primeiro paciente 
    Paciente* pac = heapPrioritario.dados[0];

    printf("Paciente prioritario chamado: %s | RG: %s | Idade: %d\n", pac->nome, pac->rg, pac->idade);

    // log da chamada
    char detalhes_json[256];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"rg\":\"%s\",\"idade\":%d}", pac->nome, pac->rg, pac->idade);
    logarOperacao("DESENFILEIRAR_PRIORITARIO", detalhes_json);

    // substitui o primeiro pelo ultimo e reequilibra a heap
    heapPrioritario.dados[0] = heapPrioritario.dados[heapPrioritario.qtde - 1];
    heapPrioritario.qtde--;
    peneirar(&heapPrioritario, 0);
}

void mostrarFilaPrioritaria() {
    // se a heap estiver vazia, aviso e log
    if (heapPrioritario.qtde == 0) {
        printf("Fila prioritaria vazia!\n");
        logarOperacao("MOSTRAR_FILA_PRIORITARIA", "{\"resultado\":\"fila vazia\"}");
        return;
    }

    printf("Fila prioritaria (por idade):\n");

    // percorre todos os elementos e exibe
    char detalhes_json[256];
    for (int i = 0; i < heapPrioritario.qtde; i++) {
        Paciente* pac = heapPrioritario.dados[i];
        printf("%d. Nome: %s | RG: %s | Idade: %d\n", i+1, pac->nome, pac->rg, pac->idade);

        // log de cada paciente individual
        snprintf(detalhes_json, sizeof(detalhes_json),
            "{\"pos\":%d,\"nome\":\"%s\",\"rg\":\"%s\",\"idade\":%d}", i+1, pac->nome, pac->rg, pac->idade);
        logarOperacao("MOSTRAR_FILA_PRIORITARIA_ITEM", detalhes_json);
    }

    // log com total de elementos
    snprintf(detalhes_json, sizeof(detalhes_json), "{\"total\":%d}", heapPrioritario.qtde);
    logarOperacao("MOSTRAR_FILA_PRIORITARIA", detalhes_json);
}

void menuAtendimentoPrioritario() {
    int op;
    do {
        printf("\n--- Atendimento Prioritario ---\n");
        printf("1. Enfileirar prioritario\n");
        printf("2. Desenfileirar prioritario\n");
        printf("3. Mostrar fila prioritaria\n");
        printf("0. Voltar\n");
        printf("-------------------------------\n");
        printf("Opcao: ");

        scanf(" %d", &op);

        // executa a acao de acordo com a opcao
        switch (op) {
            case 1: enfileirarPrioritario(); break;
            case 2: desenfileirarPrioritario(); break;
            case 3: mostrarFilaPrioritaria(); break;
            case 0: /* volta */ break;
            default: printf("Invalido!\n"); break;
        }
    } while (op != 0);
}
