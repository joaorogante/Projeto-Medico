#include <stdio.h>
#include <stdlib.h>
#include "medico.h"

void menuCadastrar();
void menuAtendimento();
void menuAtendimentoPrioritario();
void menuPesquisa();
void menuDesfazer();
void menuIO();

int main() {
    int op;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar\n");
        printf("2. Atendimento Normal\n");
        printf("3. Atendimento Prioritário\n");
        printf("4. Pesquisa (ABB)\n");
        printf("5. Desfazer Operação\n");
        printf("6. Carregar / Salvar\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha um menu: ");
        if (scanf(" %d", &op) != 1) op = 0;

        switch (op) {
            case 1:  menuCadastrar();           break;
           
        }
    } while (op != 0);

    return 0;
}

/* Sub-menu 1: Cadastro de pacientes */
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

