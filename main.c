#include <stdio.h>
#include <stdlib.h>

#include "src/Cadastro/cadastro.h"
#include "src/Atendimento/atendimento.h"
#include "src/Prioritario/prioritario.h"
#include "src/Pesquisa/pesquisa.h"
#include "src/Desfazer/desfazer.h"
#include "src/IO/io.h"
#include "src/Sobre/sobre.h"

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