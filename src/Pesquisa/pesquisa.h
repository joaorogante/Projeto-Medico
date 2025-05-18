#ifndef PESQUISA_H
#define PESQUISA_H

#include "../tipos.h"

typedef struct EABB {
    Paciente *dados;
    struct EABB *esq;
    struct EABB *dir;
} EABB;

// Funções de pesquisa/ordenacao (ABB)
void mostrarPorAno();
void mostrarPorMes();
void mostrarPorDia();
void mostrarPorIdade();
void menuPesquisa();
void inserirNaABB(Paciente *pac);
void removerDaABB(Paciente* pac);

#endif // PESQUISA_H
