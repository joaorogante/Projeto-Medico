#ifndef MEDICO_H
#define MEDICO_H

#define MAX_DIARIO 20

/* Estrutura do paciente */
typedef struct Paciente {
    char nome[100];
    int idade;
    char rg[20];
    int dia, mes, ano;
} Paciente;

/* Lista encadeada de pacientes */
void cadastrarPaciente();
void consultarPaciente();
void listarPacientes();
void atualizarPaciente();
void removerPaciente();



#endif /* MEDICO_H */
