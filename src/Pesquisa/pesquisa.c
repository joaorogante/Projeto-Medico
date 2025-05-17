#include "pesquisa.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções de pesquisa/ordenacao

void mostrarPorAno() {
    // Implementação conforme especificação
}

void mostrarPorMes() {
    // Implementação conforme especificação
}

void mostrarPorDia() {
    // Implementação conforme especificação
}

void mostrarPorIdade() {
    // Implementação conforme especificação
}

/* Sub-menu 4: Pesquisa / Ordenação via ABB */
void menuPesquisa() {
    int op;
    do {
        printf("\n--- Pesquisa / Ordenação (ABB) ---\n");
        printf("1. Ordenar por ano de registro\n");
        printf("2. Ordenar por mês de registro\n");
        printf("3. Ordenar por dia de registro\n");
        printf("4. Ordenar por idade do paciente\n");
        printf("0. Voltar\n");
        printf("---------------------------------\n");
        printf("Opção: ");

        scanf(" %d", &op);

        switch (op) {
            case 1: mostrarPorAno();    break;
            case 2: mostrarPorMes();    break;
            case 3: mostrarPorDia();    break;
            case 4: mostrarPorIdade();  break;
            case 0: /* volta */         break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}