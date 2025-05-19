#include "io.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções de I/O

void carregarDados() {
    // Implementação conforme especificação
}

void salvarDados() {
    // Implementação conforme especificação
}

/* Sub-menu 6: Carregar e salvar dados em arquivo */
void menuIO() {
    int op;
    do {
        printf("\n--- Carregar / Salvar Dados ---\n");
        printf("1. Carregar de arquivo\n");
        printf("2. Salvar em arquivo\n");
        printf("0. Voltar\n");
        printf("-------------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: carregarDados(); break;
            case 2: salvarDados();   break;
            case 0: /* volta */       break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}
