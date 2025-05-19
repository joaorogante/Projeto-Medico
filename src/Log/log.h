#ifndef LOG_H
#define LOG_H

#define MAX_LOG_OPERACOES 100

typedef struct {
    char operacao[32];      // Ex: "ENFILEIRAR" ou "DESENFILEIRAR"
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

/* Pilha global de logs (declarada em log.c) */
extern LogStack logStack;

/* Inicialização / registro / listagem genérica */
void inicializarLogStack();
void logarOperacao(const char* operacao, const char* detalhes_json);
void listarLogOperacoes();

/* NOVAS funções para desfazer somente atendimento */
LogOperacao popLogOperacao();                  // retira e devolve o topo da pilha
void listarLogAtendimento();                   // lista apenas ENFILEIRAR/DESENFILEIRAR

#endif // LOG_H
