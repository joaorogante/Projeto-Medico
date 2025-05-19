#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "../tipos.h"

// Funções da fila normal (FIFO)
void enfileirarNormal();
void desenfileirarNormal();
void mostrarFilaNormal();
void menuAtendimento();

#endif // ATENDIMENTO_H

int removerPacienteDaFilaPorRG(const char *rg);
int reinserirPacienteNoInicio(const char *rg);
