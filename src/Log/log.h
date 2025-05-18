#ifndef LOG_H
#define LOG_H

#define MAX_LOG_OPERACOES 100

typedef struct {
    char operacao[32];      // Ex: "CADASTRO"
    char usuario[64];       // Exemplo: "Sistema TOP =)"
    char dataHora[32];      // Timestamp da operação
    char detalhes[256];     // JSON com os dados da operação
} LogOperacao;

typedef struct LogCell {
    LogOperacao log;
    struct LogCell *anterior;
} LogCell;

typedef struct {
    LogCell *top;
    int qtde;
} LogStack;

void logarOperacao(const char* operacao, const char* detalhes_json);
void listarLogOperacoes();
void inicializarLogStack();

#endif
