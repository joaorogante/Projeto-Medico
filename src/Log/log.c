#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Pilha de logs agora global */
LogStack logStack = {NULL, 0};

/* Timestamp helper */
static void getTimestamp(char* buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void inicializarLogStack() {
    logStack.top = NULL;
    logStack.qtde = 0;
}

void logarOperacao(const char* operacao, const char* detalhes_json) {
    if (logStack.qtde >= MAX_LOG_OPERACOES) return;
    LogCell *nova = malloc(sizeof(LogCell));
    if (!nova) return;

    strncpy(nova->log.operacao, operacao, sizeof(nova->log.operacao)-1);
    nova->log.operacao[31] = '\0';
    strncpy(nova->log.usuario, "Sistema TOP =)", sizeof(nova->log.usuario)-1);
    nova->log.usuario[63] = '\0';
    getTimestamp(nova->log.dataHora, sizeof(nova->log.dataHora));
    strncpy(nova->log.detalhes, detalhes_json, sizeof(nova->log.detalhes)-1);
    nova->log.detalhes[255] = '\0';

    nova->anterior = logStack.top;
    logStack.top = nova;
    logStack.qtde++;
}

void listarLogOperacoes() {
    LogCell *atual = logStack.top;
    int idx = logStack.qtde;
    printf("\n--- LOG DE OPERAÇÕES ---\n");
    while (atual) {
        printf("[%d] {\"operacao\":\"%s\",\"dataHora\":\"%s\",\"detalhes\":%s}\n",
               idx,
               atual->log.operacao,
               atual->log.dataHora,
               atual->log.detalhes);
        atual = atual->anterior;
        idx--;
    }
    printf("------------------------\n");
}

/* Remove e retorna o topo da pilha */
LogOperacao popLogOperacao() {
    LogOperacao vazio = {"", "", "", ""};
    if (logStack.qtde == 0) return vazio;

    LogCell *rem = logStack.top;
    LogOperacao l = rem->log;
    logStack.top = rem->anterior;
    logStack.qtde--;
    free(rem);
    return l;
}

/* Lista apenas operações de atendimento */
void listarLogAtendimento() {
    LogCell *atual = logStack.top;
    int idx = logStack.qtde;
    printf("\n--- LOG DE ATENDIMENTO ---\n");
    while (atual) {
        if (strcmp(atual->log.operacao, "ENFILEIRAR") == 0 ||
            strcmp(atual->log.operacao, "DESENFILEIRAR") == 0) {
            printf("[%d] {\"operacao\":\"%s\",\"dataHora\":\"%s\",\"detalhes\":%s}\n",
                   idx,
                   atual->log.operacao,
                   atual->log.dataHora,
                   atual->log.detalhes);
        }
        atual = atual->anterior;
        idx--;
    }
    printf("---------------------------\n");
}
