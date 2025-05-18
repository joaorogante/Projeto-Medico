#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Pilha global de logs
static LogStack logStack = {NULL, 0};

// Função utilitária para pegar timestamp
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
    if (logStack.qtde >= MAX_LOG_OPERACOES)
        return;

    LogCell *nova = (LogCell*)malloc(sizeof(LogCell));
    if (!nova) return;

    strncpy(nova->log.operacao, operacao, sizeof(nova->log.operacao) - 1);
    nova->log.operacao[sizeof(nova->log.operacao) - 1] = '\0';

    strncpy(nova->log.usuario, "Sistema TOP =)", sizeof(nova->log.usuario) - 1);
    nova->log.usuario[sizeof(nova->log.usuario) - 1] = '\0';

    getTimestamp(nova->log.dataHora, sizeof(nova->log.dataHora));

    strncpy(nova->log.detalhes, detalhes_json, sizeof(nova->log.detalhes) - 1);
    nova->log.detalhes[sizeof(nova->log.detalhes) - 1] = '\0';

    nova->anterior = logStack.top;
    logStack.top = nova;
    logStack.qtde++;
}

void listarLogOperacoes() {
    LogCell *atual = logStack.top;
    int idx = logStack.qtde;
    while (atual) {
        printf("[%d] {\"operacao\":\"%s\", \"dataHora\":\"%s\", \"detalhes\":%s}\n",
            idx,
            atual->log.operacao,
            atual->log.dataHora,
            atual->log.detalhes);
        atual = atual->anterior;
        idx--;
    }
}
