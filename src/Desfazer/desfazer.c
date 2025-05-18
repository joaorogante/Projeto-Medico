#include "desfazer.h"
#include "../Log/log.h" 
#include <stdio.h>
#include <stdlib.h>

void mostrarLogOperacoes() {
    printf("\n--- LOG DE OPERAÇÕES ---\n");
    listarLogOperacoes();
    printf("------------------------\n");
}

void desfazerUltimaOperacao() {
    // Implementação futura
}

/* Sub-menu 5: Desfazer última operação na fila normal */
void menuDesfazer() {
    int op;
    do {
        printf("\n--- Desfazer Operações ---\n");
        printf("1. Mostrar log de operações\n");
        printf("2. Desfazer última operação\n");
        printf("0. Voltar\n");
        printf("---------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: mostrarLogOperacoes();    break;
            case 2: desfazerUltimaOperacao(); break;
            case 0: /* volta */               break;
            default: printf("Inválido!\n");   break;
        }
    } while (op != 0);
}
