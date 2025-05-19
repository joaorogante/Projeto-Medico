#include "desfazer.h"
#include "../Log/log.h"
#include "../Atendimento/atendimento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* já existente */
void mostrarLogOperacoes() {
    listarLogOperacoes();
}

/* NOVO: mostra só operações de atendimento */
void mostrarLogAtendimento() {
    listarLogAtendimento();
}

/* desfaz última inserção ou remoção na fila de atendimento */
void desfazerUltimaOperacaoAtendimento() {
    char confirm;
    printf("Tem certeza que deseja desfazer a última operação de atendimento? (S/N): ");
    scanf(" %c", &confirm);
    if (confirm != 'S' && confirm != 's') {
        printf("Operação de desfazer cancelada.\n");
        return;
    }
    
    LogOperacao log;
    /* empilha em temp até achar ENFILEIRAR/DESENFILEIRAR */
    do {
        log = popLogOperacao();
        if (log.operacao[0] == '\0') {
            printf("Nenhuma operação de atendimento encontrada para desfazer.\n");
            return;
        }
    } while (strcmp(log.operacao, "ENFILEIRAR") != 0 &&
             strcmp(log.operacao, "DESENFILEIRAR") != 0);

    /* extrai RG do JSON detalhes: {"nome":"...","rg":"<RG>"} */
    char rg[32] = "";
    char *p = strstr(log.detalhes, "\"rg\":\"");
    if (p) {
        p += 6;
        sscanf(p, "%31[^\"]", rg);
    }

    if (strcmp(log.operacao, "ENFILEIRAR") == 0) {
        /* desfazer inserção: remover paciente da fila */
        if (!removerPacienteDaFilaPorRG(rg)) {
            printf("Erro ao desfazer ENFILEIRAR: paciente não encontrado na fila.\n");
        } else {
            printf("Inserção de RG %s desfeita com sucesso!\n", rg);
        }
    } else {
        /* desfazer remoção: reinserir no início */
        if (!reinserirPacienteNoInicio(rg)) {
            printf("Erro ao desfazer DESENFILEIRAR: paciente não encontrado no cadastro.\n");
        } else {
            printf("Remoção de RG %s desfeita com sucesso!\n", rg);
        }
    }
}

/* menu principal de desfazer, com novas opções */
void menuDesfazer() {
    int op;
    do {
        printf("\n--- Desfazer Operações ---\n");
        printf("1. Mostrar log de operações\n");
        printf("2. Mostrar logs de atendimento\n");
        printf("3. Desfazer última operação de atendimento\n");
        printf("0. Voltar\n");
        printf("---------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);
        switch (op) {
            case 1: mostrarLogOperacoes();                      break;
            case 2: mostrarLogAtendimento();                    break;
            case 3: desfazerUltimaOperacaoAtendimento();        break;
            case 0: /* volta */                                 break;
            default: printf("Inválido!\n");                     break;
        }
    } while (op != 0);
}
