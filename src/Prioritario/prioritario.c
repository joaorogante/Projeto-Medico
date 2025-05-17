#include "prioritario.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções do heap prioritário

void enfileirarPrioritario() {
    // Implementação conforme especificação
}

void desenfileirarPrioritario() {
    // Implementação conforme especificação
}

void mostrarFilaPrioritaria() {
    // Implementação conforme especificação
}

/* Sub-menu 3: Atendimento Prioritário (max-heap) */
void menuAtendimentoPrioritario() {
    int op;
    do {
        printf("\n--- Atendimento Prioritário ---\n");
        printf("1. Enfileirar prioritário\n");
        printf("2. Desenfileirar prioritário\n");
        printf("3. Mostrar fila prioritária\n");
        printf("0. Voltar\n");
        printf("-------------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: enfileirarPrioritario();    break;
            case 2: desenfileirarPrioritario(); break;
            case 3: mostrarFilaPrioritaria();   break;
            case 0: /* volta */                 break;
            default: printf("Inválido!\n");     break;
        }
    } while (op != 0);
}