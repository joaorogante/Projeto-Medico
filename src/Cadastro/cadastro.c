#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação das funções de cadastro

void cadastrarPaciente() {
    // Implementação conforme especificação
}

void consultarPaciente() {
    // Implementação conforme especificação
}

void listarPacientes() {
    // Implementação conforme especificação
}

void atualizarPaciente() {
    // Implementação conforme especificação
}

void removerPaciente() {
    // Implementação conforme especificação
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

        /* Lê opção do usuário */
        scanf(" %d", &op);

        /* Executa função de cadastro correspondente */
        switch (op) {
            case 1: cadastrarPaciente();   break;
            case 2: consultarPaciente();   break;
            case 3: listarPacientes();     break;
            case 4: atualizarPaciente();   break;
            case 5: removerPaciente();     break;
            case 0: /* retorna ao menu principal */ break;
            default: printf("Inválido!\n"); break;
        }
    } while (op != 0);
}