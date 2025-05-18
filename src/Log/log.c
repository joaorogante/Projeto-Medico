#include "log.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static LogOperacao logOperacoes[MAX_LOG_OPERACOES];
static int logCount = 0;

// Função utilitária para pegar timestamp
static void getTimestamp(char* buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void logarOperacao(const char* operacao, const char* detalhes_json) {
    if (logCount >= MAX_LOG_OPERACOES) return;
    strncpy(logOperacoes[logCount].operacao, operacao, sizeof(logOperacoes[logCount].operacao) - 1);
    logOperacoes[logCount].operacao[sizeof(logOperacoes[logCount].operacao) - 1] = '\0';

    strncpy(logOperacoes[logCount].usuario, "Sistema TOP =)", sizeof(logOperacoes[logCount].usuario) - 1);
    logOperacoes[logCount].usuario[sizeof(logOperacoes[logCount].usuario) - 1] = '\0';

    getTimestamp(logOperacoes[logCount].dataHora, sizeof(logOperacoes[logCount].dataHora));

    strncpy(logOperacoes[logCount].detalhes, detalhes_json, sizeof(logOperacoes[logCount].detalhes) - 1);
    logOperacoes[logCount].detalhes[sizeof(logOperacoes[logCount].detalhes) - 1] = '\0';

    logCount++;
}

void listarLogOperacoes() {
    for (int i = 0; i < logCount; ++i) {
        printf("{\"operacao\":\"%s\", \"dataHora\":\"%s\", \"detalhes\":%s}\n",
            logOperacoes[i].operacao,
            logOperacoes[i].dataHora,
            logOperacoes[i].detalhes);
    }
}
