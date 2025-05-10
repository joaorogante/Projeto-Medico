#include <stdio.h>
#include <stdlib.h>
#include "medico.h"

/* Protótipos dos sub-menus */
void menuCadastrar();
void menuAtendimento();
void menuAtendimentoPrioritario();
void menuPesquisa();
void menuDesfazer();
void menuIO();

int main() {
    int op;

    do {
        /* Menu principal */
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar\n");
        printf("2. Atendimento Normal\n");
        printf("3. Atendimento Prioritário\n");
        printf("4. Pesquisa (ABB)\n");
        printf("5. Desfazer Operação\n");
        printf("6. Carregar / Salvar\n");
        printf("7. Sobre\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha um menu: ");

        /* Lê opção do usuário; se scanf falhar, sai */
        if (scanf(" %d", &op) != 1) {
            op = 0;
        }

        /* Dispara o sub-menu ou ação correspondente */
        switch (op) {
            case 1:  menuCadastrar();            break;
            case 2:  menuAtendimento();          break;
            case 3:  menuAtendimentoPrioritario(); break;
            case 4:  menuPesquisa();             break;
            case 5:  menuDesfazer();             break;
            case 6:  menuIO();                   break;
            case 7:  mostrarSobre();             break;
            case 0:  printf("Saindo...\n");      break;
            default: printf("Opção inválida!\n"); break;
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

/* Sub-menu 2: Atendimento Normal (fila FIFO) */
void menuAtendimento() {
    int op;
    do {
        printf("\n--- Atendimento Normal ---\n");
        printf("1. Enfileirar\n");
        printf("2. Desenfileirar\n");
        printf("3. Mostrar fila\n");
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
