#include "atendimento.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções da fila normal

void enfileirarNormal() {
    // Implementação conforme especificação
}

void desenfileirarNormal() {
    // Implementação conforme especificação
}

void mostrarFilaNormal() {
    // Implementação conforme especificação
}

/* Sub-menu 2: Atendimento Normal (fila FIFO) */
void menuAtendimento() {
    int op;
    do {
        printf("\n--- Atendimento Normal ---\n");
        printf("1. Enfileirar Paciente\n");
        printf("2. Desenfileirar Paciente\n");
        printf("3. Mostrar fila de Paciente\n");
        printf("0. Voltar\n");
        printf("-------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: enfileirarNormal();    break;
            case 2: desenfileirarNormal(); break;
            case 3: mostrarFilaNormal();   break;
            case 0: /* volta */            break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}