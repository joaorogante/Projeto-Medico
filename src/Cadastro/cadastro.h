#ifndef CADASTRO_H
#define CADASTRO_H

#include "../tipos.h"

void cadastrarPaciente();
void consultarPaciente();
void listarPacientes();
void atualizarPaciente();
void removerPaciente();
void menuCadastrar();

Paciente* getPacientePorRG(const char* rg);

#endif 
