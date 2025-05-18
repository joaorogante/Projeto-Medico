#include "cadastro.h"
#include "../Log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ELista {
    Paciente dados;
    struct ELista *proximo;
} ELista;

typedef struct {
    ELista *inicio;
    int qtde;
} Lista;

// cria a lista
static Lista listaPacientes = {NULL, 0};

void cadastrarPaciente() {
    // cria ELista que recebe o novo paciente
    ELista *novo = (ELista*)malloc(sizeof(ELista));
    if (!novo) {
        printf("Erro de memória!\n");
        return;
    }

    // salva os dados dos novos pacientes
    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Idade: ");
    scanf("%d", &novo->dados.idade);
    printf("RG: ");
    scanf(" %[^\n]", novo->dados.rg);
    printf("Data de entrada (dd mm aaaa): ");
    scanf("%d %d %d", &novo->dados.dia, &novo->dados.mes, &novo->dados.ano);

    // insiro o novo paciente no comeco da lista
    novo->proximo = listaPacientes.inicio;
    listaPacientes.inicio = novo;
    listaPacientes.qtde++;

    printf("Paciente cadastrado com sucesso!\n");

    // crio a estrtura json para o log
    char detalhes_json[1024];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
        novo->dados.nome, novo->dados.idade, novo->dados.rg,
        novo->dados.dia, novo->dados.mes, novo->dados.ano);
    logarOperacao("CADASTRO", detalhes_json);
}

void consultarPaciente() {
    char rg[20];
    printf("Digite o RG do paciente: ");
    scanf(" %[^\n]", rg);

    // percorro a lista procurando pelo rg
    ELista *atual = listaPacientes.inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados.rg, rg) == 0) {
            // se achar, mostro os dados
            printf("Nome: %s\n", atual->dados.nome);
            printf("Idade: %d\n", atual->dados.idade);
            printf("RG: %s\n", atual->dados.rg);
            printf("Data de entrada: %02d/%02d/%04d\n", atual->dados.dia, atual->dados.mes, atual->dados.ano);

            // log da operacao com os dados encontrados
            char detalhes_json[1024];
            snprintf(detalhes_json, sizeof(detalhes_json),
                "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
                atual->dados.nome, atual->dados.idade, atual->dados.rg,
                atual->dados.dia, atual->dados.mes, atual->dados.ano);
            logarOperacao("CONSULTA", detalhes_json);
            return;
        }
        atual = atual->proximo;
    }

    printf("Paciente não encontrado!\n");
    logarOperacao("CONSULTA", "{\"resultado\":\"nao encontrado\"}");
}

// Essa nao é utlizada nesse menu, e sim por outro modulos, como o atendimento
Paciente* getPacientePorRG(const char* rg) {
    ELista *atual = listaPacientes.inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados.rg, rg) == 0) {

            char detalhes_json[1024];
            snprintf(detalhes_json, sizeof(detalhes_json),
                "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
                atual->dados.nome, atual->dados.idade, atual->dados.rg,
                atual->dados.dia, atual->dados.mes, atual->dados.ano);
            logarOperacao("CONSULTA", detalhes_json);

            return &atual->dados;
        }
        atual = atual->proximo;
    }
    printf("Paciente não encontrado!\n");
    logarOperacao("CONSULTA", "{\"resultado\":\"nao encontrado\"}");
    return NULL;
}


void listarPacientes() {
    ELista *atual = listaPacientes.inicio;
    if (!atual) {
        // se a lista estiver vazia, aviso e log
        printf("Lista vazia!\n");
        logarOperacao("LISTAR", "{\"resultado\":\"vazia\"}");
        return;
    }

    printf("Pacientes cadastrados:\n");
    char detalhes_json[1024];
    int count = 0;

    // percorro a lista printando e logando cada paciente
    while (atual != NULL) {
        printf("Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
            atual->dados.nome, atual->dados.idade, atual->dados.rg,
            atual->dados.dia, atual->dados.mes, atual->dados.ano);

        snprintf(detalhes_json, sizeof(detalhes_json),
            "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
            atual->dados.nome, atual->dados.idade, atual->dados.rg,
            atual->dados.dia, atual->dados.mes, atual->dados.ano);
        logarOperacao("LISTAR_ITEM", detalhes_json);

        atual = atual->proximo;
        count++;
    }

    // log com o total de pacientes listados
    snprintf(detalhes_json, sizeof(detalhes_json), "{\"total\":%d}", count);
    logarOperacao("LISTAR", detalhes_json);
}

void atualizarPaciente() {
    char rg[20];
    printf("Digite o RG do paciente a atualizar: ");
    scanf(" %[^\n]", rg);

    ELista *atual = listaPacientes.inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados.rg, rg) == 0) {
            // salvo os dados antigos
            char detalhes_antes[256];
            snprintf(detalhes_antes, sizeof(detalhes_antes),
                "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
                atual->dados.nome, atual->dados.idade, atual->dados.rg,
                atual->dados.dia, atual->dados.mes, atual->dados.ano);

            // pego os novos dados do usuario
            printf("Novo nome (atual: %s): ", atual->dados.nome);
            scanf(" %[^\n]", atual->dados.nome);
            printf("Nova idade (atual: %d): ", atual->dados.idade);
            scanf("%d", &atual->dados.idade);
            printf("Nova data de entrada (atual: %02d/%02d/%04d): ", atual->dados.dia, atual->dados.mes, atual->dados.ano);
            scanf("%d %d %d", &atual->dados.dia, &atual->dados.mes, &atual->dados.ano);
            printf("Dados atualizados!\n");

            // salvo os novos dados
            char detalhes_depois[256];
            snprintf(detalhes_depois, sizeof(detalhes_depois),
                "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
                atual->dados.nome, atual->dados.idade, atual->dados.rg,
                atual->dados.dia, atual->dados.mes, atual->dados.ano);

            // monto json com antes e depois
            char detalhes_json[1024];
            snprintf(detalhes_json, sizeof(detalhes_json),
                "{\"rg\":\"%s\", \"antes\":%s, \"depois\":%s}",
                rg, detalhes_antes, detalhes_depois);

            // log da atualizacao
            logarOperacao("ATUALIZAR", detalhes_json);
            return;
        }
        atual = atual->proximo;
    }

    printf("Paciente não encontrado!\n");
    logarOperacao("ATUALIZAR", "{\"resultado\":\"nao encontrado\"}");
}

void removerPaciente() {
    char rg[20];
    printf("Digite o RG do paciente a remover: ");
    scanf(" %[^\n]", rg);

    ELista *anterior = NULL;
    ELista *atual = listaPacientes.inicio;

    // procuro o paciente na lista
    while (atual != NULL && strcmp(atual->dados.rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        // se nao achar, aviso e log
        printf("Paciente não encontrado!\n");
        logarOperacao("REMOVER", "{\"resultado\":\"nao encontrado\"}");
        return;
    }

    // salvo os dados do paciente antes de remover
    char detalhes_json[1024];
    snprintf(detalhes_json, sizeof(detalhes_json),
        "{\"nome\":\"%s\",\"idade\":%d,\"rg\":\"%s\",\"data\":\"%02d/%02d/%04d\"}",
        atual->dados.nome, atual->dados.idade, atual->dados.rg,
        atual->dados.dia, atual->dados.mes, atual->dados.ano);

    // tiro o paciente da lista
    if (anterior == NULL) {
        listaPacientes.inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    listaPacientes.qtde--;

    printf("Paciente removido!\n");
    logarOperacao("REMOVER", detalhes_json);
}

void menuCadastrar() {
    int op;
    do {
        printf("\n--- Cadastro de Pacientes ---\n");
        printf("1. Cadastrar novo\n");
        printf("2. Consultar (por RG)\n");
        printf("3. Listar todos\n");
        printf("4. Atualizar dados\n");
        printf("5. Remover paciente\n");
        printf("0. Voltar\n");
        printf("-----------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: cadastrarPaciente();   break;
            case 2: consultarPaciente();   break;
            case 3: listarPacientes();     break;
            case 4: atualizarPaciente();   break;
            case 5: removerPaciente();     break;
            case 0: break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}
